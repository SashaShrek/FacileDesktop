gcc bin/FacileDesktop.c -o out/FacileDesktop `pkg-config --cflags --libs gtk+-3.0`
cp ui/MainGUI.ui out/MainGUI.ui