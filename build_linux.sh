gcc bin/FacileDesktop.c bin/Settings.c bin/AddTask.c -c `pkg-config --cflags --libs gtk+-3.0`
gcc FacileDesktop.o Settings.o AddTask.o -o out/FacileDesktop `pkg-config --cflags --libs gtk+-3.0`

mv FacileDesktop.o object/FacileDesktop.o
mv Settings.o object/Settings.o
mv AddTask.o object/AddTask.o

cp ui/MainGUI.ui out/MainGUI.ui
cp ui/SettingsGUI.ui out/SettingsGUI.ui
cp ui/AddTaskGUI.ui out/AddTaskGUI.ui