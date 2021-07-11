TEMPLATE = subdirs

CONFIG += c++14

SUBDIRS = src

# src.depends = libs
# tests.depends = libs

TRANSLATIONS += src/cn.ts \
                src/en.ts
