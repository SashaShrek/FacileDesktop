gcc bin/FacileDesktop.c bin/Settings.h -o out/FacileDesktop `pkg-config --cflags --libs gtk+-3.0`
cp ui/MainGUI.ui out/MainGUI.ui
cp ui/SettingsGUI.ui out/SettingsGUI.ui