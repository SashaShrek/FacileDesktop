TARGET = FacileDesktop
SRC = bin/FacileDesktop.c bin/AddTask.c bin/OnPass.c bin/OnSync.c bin/Settings.c bin/Book.c
SRCCLN = out/MainGUI.ui out/SettingsGUI.ui out/AddTaskGUI.ui out/OnPassGUI.ui out/OnSyncGUI.ui out/$(TARGET)
PREFIX = /usr/local/bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o out/$(TARGET) `pkg-config --cflags --libs gtk+-3.0`
	cp ui/MainGUI.ui out/MainGUI.ui
	cp ui/SettingsGUI.ui out/SettingsGUI.ui
	cp ui/AddTaskGUI.ui out/AddTaskGUI.ui
	cp ui/OnPassGUI.ui out/OnPassGUI.ui
	cp ui/OnSyncGUI.ui out/OnSyncGUI.ui

clean:
	rm -rf $(SRCCLN)
