gcc bin/FacileDesktop.c bin/Settings.c bin/AddTask.c bin/OnPass.c -c `pkg-config --cflags --libs gtk+-3.0`
gcc FacileDesktop.o Settings.o AddTask.o OnPass.o -o out/FacileDesktop `pkg-config --cflags --libs gtk+-3.0`

mkdir -p object

mv FacileDesktop.o object/FacileDesktop.o
mv Settings.o object/Settings.o
mv AddTask.o object/AddTask.o
mv OnPass.o object/OnPass.o

cp ui/MainGUI.ui out/MainGUI.ui
cp ui/SettingsGUI.ui out/SettingsGUI.ui
cp ui/AddTaskGUI.ui out/AddTaskGUI.ui
cp ui/OnPassGUI.ui out/OnPassGUI.ui