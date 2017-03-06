#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T13:41:13
#
#-------------------------------------------------

QT       += core gui sql                       # Added the SQL lib to have datbase related classes and functions
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Personnell_Management
TEMPLATE = app


SOURCES += main.cpp\
        frontpage.cpp \
    n1_permanent.cpp \
    n2_contract.cpp \
    n3_salesman.cpp \
    o1_showall.cpp

HEADERS  += frontpage.h \
    n1_permanent.h \
    n2_contract.h \
    n3_salesman.h \
    o1_showall.h

FORMS    += frontpage.ui \
    n1_permanent.ui \
    n2_contract.ui \
    n3_salesman.ui \
    o1_showall.ui
