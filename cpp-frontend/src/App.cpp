/*
Copyright (©) 2024  Frosty515

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "App.hpp"

#include <unistd.h>

#include <thread>

#include <Server.hpp>
#include <PinControl.hpp>

#define PIN_COUNT 14

GtkWidget* g_win;
GtkWidget* g_grid;
GtkWidget* g_labels[PIN_COUNT];
GtkWidget* g_state_buttons[PIN_COUNT];
GtkWidget* g_mode_buttons[PIN_COUNT];
GtkWidget* g_state_labels[PIN_COUNT];

std::thread* updateThread;

void update() {
    while (true) {
        for (int i = 2; i < PIN_COUNT; i++) {
            bool isOn = ReadPin(i);
            if (g_mode_buttons[i] != NULL) {
                const char* mode = gtk_button_get_label(GTK_BUTTON(g_mode_buttons[i]));
                if (strcmp(mode, "OUTPUT") == 0) {
                    if (isOn)
                        gtk_button_set_label(GTK_BUTTON(g_state_buttons[i]), "HIGH");
                    else
                        gtk_button_set_label(GTK_BUTTON(g_state_buttons[i]), "LOW");
                }
                else {
                    if (isOn)
                        gtk_label_set_text(GTK_LABEL(g_state_labels[i]), "HIGH");
                    else
                        gtk_label_set_text(GTK_LABEL(g_state_labels[i]), "LOW");
                }
            }
        }
        sleep(1);
    }
}

void click_state_button(GtkButton* button, gpointer data) {
    int pin = GPOINTER_TO_INT(data);
    bool isOn;
    const char* label = gtk_button_get_label(button);
    if (strcmp(label, "LOW") == 0) {
        gtk_button_set_label(button, "HIGH");
        isOn = true;
    }
    else {
        gtk_button_set_label(button, "LOW");
        isOn = false;
    }
    WritePin(pin, isOn);
}

void click_mode_button(GtkButton* button, gpointer data) {
    int pin = GPOINTER_TO_INT(data);
    bool mode; // true = output, false = input
    const char* label = gtk_button_get_label(button);
    if (strcmp(label, "OUTPUT") == 0) {
        gtk_button_set_label(button, "INPUT");
        mode = false;
    }
    else {
        gtk_button_set_label(button, "OUTPUT");
        mode = true;
    }
    if (!mode) {
        g_state_labels[pin] = gtk_label_new("LOW");
        gtk_grid_remove(GTK_GRID(g_grid), GTK_WIDGET(g_state_buttons[pin]));
        gtk_grid_attach(GTK_GRID(g_grid), g_state_labels[pin], 1, pin, 1, 1);
    }
    else {
        g_state_buttons[pin] = gtk_button_new_with_label("LOW");
        g_signal_connect(g_state_buttons[pin], "clicked", G_CALLBACK(click_state_button), GINT_TO_POINTER(pin));
        gtk_grid_remove(GTK_GRID(g_grid), GTK_WIDGET(g_state_labels[pin]));
        gtk_grid_attach(GTK_GRID(g_grid), g_state_buttons[pin], 1, pin, 1, 1);
    }
    ConfigPinMode(pin, mode);
}

void app_activate(GApplication* app, gpointer) {
    Server::SetURL("http://localhost:8080");
    g_win = gtk_window_new();
    gtk_window_set_application(GTK_WINDOW(g_win), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(g_win), "Arduino Server");
    gtk_window_set_default_size(GTK_WINDOW(g_win), 200, 400);

    g_grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(g_win), g_grid);

    for (int i = 0; i < PIN_COUNT; i++) {
        char label[10];
        snprintf(label, 10, "Pin %d", i);
        g_labels[i] = gtk_label_new(label);
        // set padding
        gtk_widget_set_margin_start(g_labels[i], 10);
        gtk_widget_set_margin_end(g_labels[i], 10);
        gtk_grid_attach(GTK_GRID(g_grid), g_labels[i], 0, i, 1, 1);

        g_state_buttons[i] = gtk_button_new_with_label("LOW");
        gtk_grid_attach(GTK_GRID(g_grid), g_state_buttons[i], 1, i, 1, 1);
        g_signal_connect(g_state_buttons[i], "clicked", G_CALLBACK(click_state_button), GINT_TO_POINTER(i));

        // g_state_labels[i] = gtk_label_new("LOW");

        g_mode_buttons[i] = gtk_button_new_with_label("OUTPUT");
        gtk_grid_attach(GTK_GRID(g_grid), g_mode_buttons[i], 2, i, 1, 1);
        g_signal_connect(g_mode_buttons[i], "clicked", G_CALLBACK(click_mode_button), GINT_TO_POINTER(i));
    }

    gtk_window_present(GTK_WINDOW(g_win));

    updateThread = new std::thread(update);
}