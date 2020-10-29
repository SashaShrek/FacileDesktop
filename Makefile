TARGET = FacileDesktop
SRC = bin/FacileDesktop.c bin/AddTask.c bin/OnPass.c bin/OnSync.c bin/Settings.c
#out/MainGUI.ui out/SettingsGUI.ui out/AddTaskGUI.ui out/OnPassGUI.ui out/OnSyncGUI.ui
SRCCLN = out/$(TARGET)
PREFIX = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o out/$(TARGET) `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -rf $(SRCCLN)

install:
	cp out/$(TARGET) $(PREFIX)/$(TARGET)
	cp ui/MainGUI.ui $(PREFIX)/MainGUI.ui
	cp ui/SettingsGUI.ui $(PREFIX)/SettingsGUI.ui
	cp ui/AddTaskGUI.ui $(PREFIX)/AddTaskGUI.ui
	cp ui/OnPassGUI.ui $(PREFIX)/OnPassGUI.ui
	cp ui/OnSyncGUI.ui $(PREFIX)/OnSyncGUI.ui
	cp -r out/Icon $(PREFIX)/Icon
	install out/$(TARGET) $(PREFIX)


uninstall:
	rm -rf $(PREFIX)/*.ui $(PREFIX)/$(TARGET) $(PREFIX)/Icon
