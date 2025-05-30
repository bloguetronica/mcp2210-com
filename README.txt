This package contains all the necessary files and scripts to install MCP2210
Commander (a graphical application that can be used to control and interact
with MCP2210 devices). The scripts included here are compatible with most
32-bit and 64-bit Debian based operating systems (e.g. Kubuntu, etc). Prior to
installation, you must certify that your system is Debian based (or at least
uses apt-get) and that you have an active Internet connection.

A list of the included scripts follows:
– install-rules.sh;
– install.sh;
– uninstall-rules.sh;
– uninstall.sh.

In order to compile and install MCP2210 Commander for the first time, all you
have to do is to run "install.sh" by invoking "sudo ./install.sh" on a
terminal window, after changing your working directory to the current one.
This script will first obtain and install the required "build-essential",
"libusb-1.0-0-dev" and "qt5-default"/"qtbase5-dev" packages (if they are not
installed yet). Then it will compile the application and move it to
"/usr/local/bin/".

The above mentioned installation script won't create any rules to access
Silicon Labs devices. If you don't have equivalent rules for accessing such
devices (with VID 0x04d8), you must run "install-rules.sh" too, which should
be done by invoking "sudo ./install-rules.sh".

To uninstall, you should run "uninstall.sh" by invoking "sudo ./uninstall.sh",
again on a terminal window after making sure that your working directory is
this one. This will delete the previously installed application and source
code. However it won't remove the packages mentioned above, since they could
be already installed before the first installation. This script will also not
remove the previously created rules (if applicable) and, therefore, you should
run "uninstall-rules.sh" by invoking "sudo ./uninstall-rules.sh" if you wish
to do so.

P.S.:
Since the application was designed having KDE in mind, you should get the best
rendering on Kubuntu and other Debian based systems that employ the above
desktop environment. However, the application can be perfectly used on systems
that have other desktop environments (e.g. Gnome, Xfce).
