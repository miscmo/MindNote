#include "StyleParser.h"

#include <QFont>
#include <QFontDatabase>
#include <QPalette>
#include <QPlainTextEdit>


using namespace MyNote;

static QString availableFontFamilyFromPreferenceList(QString familyList)
{
    QStringList preferredFamilies = familyList.split(',', Qt::SkipEmptyParts);

    QFontDatabase fontDB;
    QStringList availableFamilies = fontDB.families();

    foreach (QString familyPreference, preferredFamilies)
    {
        QString trimmedPref = familyPreference.trimmed().toLower();
        // Docs say: If a family exists in several foundries, the returned
        // name for that font is in the form "family [foundry]".
        // Examples: "Times [Adobe]", "Times [Cronyx]", "Palatino".
        foreach (QString availableFamily, availableFamilies)
        {
            QString trimmedAvailableFamily(availableFamily);
            int foundryNameStartIndex = trimmedAvailableFamily.lastIndexOf("[");
            if (foundryNameStartIndex != -1)
                trimmedAvailableFamily = trimmedAvailableFamily.left(foundryNameStartIndex);
            trimmedAvailableFamily = trimmedAvailableFamily.trimmed().toLower();
            if (trimmedAvailableFamily == trimmedPref)
                return availableFamily;
        }
    }

    return QString();
}

static QColor colorFromARGBStyle(pmh_attr_argb_color *color)
{
    QColor qcolor;
    qcolor.setAlpha(color->alpha);
    qcolor.setRed(color->red);
    qcolor.setGreen(color->green);
    qcolor.setBlue(color->blue);
    return qcolor;
}

static QBrush brushFromARGBStyle(pmh_attr_argb_color *color)
{
    return QBrush(colorFromARGBStyle(color));
}

static QTextCharFormat getCharFormatFromStyleAttributes(pmh_style_attribute *list,
                                                        QFont baseFont)
{
    QTextCharFormat format;
    while (list != NULL)
    {
        switch (list->type) {
        case pmh_attr_type_foreground_color:
            format.setForeground(brushFromARGBStyle(list->value->argb_color));
            break;

        case pmh_attr_type_background_color:
            format.setBackground(brushFromARGBStyle(list->value->argb_color));
            break;

        case pmh_attr_type_font_style:
            {
            if (list->value->font_styles->bold)
                format.setFontWeight(QFont::Bold);
            if (list->value->font_styles->italic)
                format.setFontItalic(true);
            if (list->value->font_styles->underlined)
                format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
            }
            break;

        case pmh_attr_type_font_size_pt:
            {
            qreal finalSize = list->value->font_size->size_pt;
            int baseFontSize = baseFont.pointSize();
            if (baseFontSize == -1)
                baseFontSize = 12; // fallback default
            if (list->value->font_size->is_relative)
                finalSize += baseFontSize;
            if (0 < finalSize)
                format.setFontPointSize(finalSize);
            }
            break;

        case pmh_attr_type_font_family:
            {
            QString familyList(list->value->font_family);
            QString availableFamily = availableFontFamilyFromPreferenceList(familyList);
            if (!availableFamily.isNull())
                format.setFontFamily(availableFamily);
            }
            break;

        default:
            break;
        }

        list = list->next;
    }
    return format;
}


void styleParserErrorCallback(char *errorMessage, int lineNumber, void *context)
{
    ((StyleParser*)context)->handleStyleParsingError(errorMessage, lineNumber);
}



StyleParser::StyleParser(const QString &styleSheet) {
    m_pStyles = pmh_parse_styles(styleSheet.toLocal8Bit().data(), &styleParserErrorCallback, this);
}


StyleParser::~StyleParser()
{
    pmh_free_style_collection(m_pStyles);
}

QVector<HighlightingStyle> StyleParser::highlightingStyles(QFont baseFont) const
{
    QVector<HighlightingStyle> highlightingStyles;
    highlightingStyles.reserve(pmh_NUM_LANG_TYPES);

    for (int i = 0; i < pmh_NUM_LANG_TYPES; i++) {
        pmh_style_attribute *attr  = m_pStyles->element_styles[i];
        if (!attr)
            continue;

        pmh_element_type type = attr->lang_element_type;
        QTextCharFormat format = getCharFormatFromStyleAttributes(attr, baseFont);

        HighlightingStyle style;
        style.format = format;
        style.type = type;
        highlightingStyles.append(style);
    }

    return highlightingStyles;
}

QPalette StyleParser::editorPalette() const
{
    static bool hasBeenCached = false;
    static QPalette defaultPalette;
    if (!hasBeenCached) {
        QPlainTextEdit pte;
        defaultPalette = pte.palette();
        hasBeenCached = true;
    }

    QPalette palette = defaultPalette;

    // Editor area styles
    if (m_pStyles->editor_styles != NULL)
    {
        pmh_style_attribute *cur = m_pStyles->editor_styles;
        while (cur != NULL)
        {
            if (cur->type == pmh_attr_type_background_color)
                palette.setColor(QPalette::Base, colorFromARGBStyle(cur->value->argb_color));
            else if (cur->type == pmh_attr_type_foreground_color)
                palette.setColor(QPalette::Text, colorFromARGBStyle(cur->value->argb_color));
            cur = cur->next;
        }
    }

    // Selection styles
    if (m_pStyles->editor_selection_styles != NULL)
    {
        pmh_style_attribute *cur = m_pStyles->editor_selection_styles;
        while (cur != NULL)
        {
            if (cur->type == pmh_attr_type_background_color)
                palette.setColor(QPalette::Highlight, colorFromARGBStyle(cur->value->argb_color));
            else if (cur->type == pmh_attr_type_foreground_color)
                palette.setColor(QPalette::HighlightedText, colorFromARGBStyle(cur->value->argb_color));
            cur = cur->next;
        }
    }

    return palette;
}




void StyleParser::handleStyleParsingError(char *errorMessage, int lineNumber)
{
    m_lStyleParsingErrorList.append(QPair<int,QString>(lineNumber, QString(errorMessage)));
}
