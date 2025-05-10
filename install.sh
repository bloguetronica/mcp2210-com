#!/bin/sh

echo Obtaining required packages...
apt-get -qq update
apt-get -qq install build-essential
apt-get -qq install libusb-1.0-0-dev
apt-get -qq install qt5-default
apt-get -qq install qtbase5-dev
echo Copying source code files...
mkdir -p /usr/local/src/mcp2210-com/icons/buttons
mkdir -p /usr/local/src/mcp2210-com/images
mkdir -p /usr/local/src/mcp2210-com/misc
mkdir -p /usr/local/src/mcp2210-com/translations
cp -f src/aboutdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/aboutdialog.h /usr/local/src/mcp2210-com/.
cp -f src/aboutdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/chipsettingsdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/chipsettingsdialog.h /usr/local/src/mcp2210-com/.
cp -f src/chipsettingsdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/common.cpp /usr/local/src/mcp2210-com/.
cp -f src/common.h /usr/local/src/mcp2210-com/.
cp -f src/cssettingsdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/cssettingsdialog.h /usr/local/src/mcp2210-com/.
cp -f src/cssettingsdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/data.cpp /usr/local/src/mcp2210-com/.
cp -f src/data.h /usr/local/src/mcp2210-com/.
cp -f src/delaysdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/delaysdialog.h /usr/local/src/mcp2210-com/.
cp -f src/delaysdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/devicewindow.cpp /usr/local/src/mcp2210-com/.
cp -f src/devicewindow.h /usr/local/src/mcp2210-com/.
cp -f src/devicewindow.ui /usr/local/src/mcp2210-com/.
cp -f src/icons/active64.png /usr/local/src/mcp2210-com/icons/.
cp -f src/icons/buttons/clipboard-copy.png /usr/local/src/mcp2210-com/icons/buttons/.
cp -f src/icons/buttons/clipboard-copy.svg /usr/local/src/mcp2210-com/icons/buttons/.
cp -f src/icons/buttons/clipboard-paste.png /usr/local/src/mcp2210-com/icons/buttons/.
cp -f src/icons/buttons/clipboard-paste.svg /usr/local/src/mcp2210-com/icons/buttons/.
cp -f src/icons/greyed64.png /usr/local/src/mcp2210-com/icons/.
cp -f src/icons/icon.svg /usr/local/src/mcp2210-com/icons/.
cp -f src/icons/mcp2210-com.png /usr/local/src/mcp2210-com/icons/.
cp -f src/icons/selected64.png /usr/local/src/mcp2210-com/icons/.
cp -f src/images/banner.png /usr/local/src/mcp2210-com/images/.
cp -f src/images/banner.svg /usr/local/src/mcp2210-com/images/.
cp -f src/informationdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/informationdialog.h /usr/local/src/mcp2210-com/.
cp -f src/informationdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/libusb-extra.c /usr/local/src/mcp2210-com/.
cp -f src/libusb-extra.h /usr/local/src/mcp2210-com/.
cp -f src/main.cpp /usr/local/src/mcp2210-com/.
cp -f src/mainwindow.cpp /usr/local/src/mcp2210-com/.
cp -f src/mainwindow.h /usr/local/src/mcp2210-com/.
cp -f src/mainwindow.ui /usr/local/src/mcp2210-com/.
cp -f src/mcp2210-com.pro /usr/local/src/mcp2210-com/.
cp -f src/mcp2210.cpp /usr/local/src/mcp2210-com/.
cp -f src/mcp2210.h /usr/local/src/mcp2210-com/.
cp -f src/misc/mcp2210-com.desktop /usr/local/src/mcp2210-com/misc/.
cp -f src/resources.qrc /usr/local/src/mcp2210-com/.
cp -f src/statusdialog.cpp /usr/local/src/mcp2210-com/.
cp -f src/statusdialog.h /usr/local/src/mcp2210-com/.
cp -f src/statusdialog.ui /usr/local/src/mcp2210-com/.
cp -f src/translations/mcp2210-com_en.qm /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_en.ts /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_en_US.qm /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_en_US.ts /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_pt.qm /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_pt.ts /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_pt_PT.qm /usr/local/src/mcp2210-com/translations/.
cp -f src/translations/mcp2210-com_pt_PT.ts /usr/local/src/mcp2210-com/translations/.
echo Building and installing application...
cd /usr/local/src/mcp2210-com
qmake
make install clean
rm -f mcp2210-com
echo Done!
