/* window.vala
 *
 * Copyright 2019 Shiqi Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace FileSelect {
	[GtkTemplate (ui = "/com/github/liushiqi/MultipleSort/file_select.ui")]
	public class Window : Gtk.ApplicationWindow {
	    [GtkChild]
	    private Gtk.FileChooserButton file_select;

	    [GtkCallback]
	    public void confirm_button_clicked() {
	        close();
			debug("Open Keyword Select with file path: %s", file_select.get_filename());
	        Gtk.Window window = new KeyWordSelect.Window(this.application, file_select.get_file());
	        window.present();
	    }

		public Window(Gtk.Application app, File? file) {
			Object(application: app);
			if (file != null) {
			    try {
    			    file_select.set_file(file);
			    } catch (Error e) {
			        error("Why this happens?");
			    }
			}
		}
	}
}

private class Row {
    public string[] elems;

    public Row(string[] elems) {
        this.elems = elems;
    }
}

delegate bool Compare(Row i, Row j);

void merge_sort(Row[] elems, Compare comp) {
    int len = elems.length;
    if (len == 1 || len == 0) return;
    Row[] left = elems[0:len / 2];
    Row[] right = elems[len / 2:len];
    merge_sort(left, comp);
    merge_sort(right, comp);
    int i = 0, j = 0, k = 0;
    while (k < elems.length) {
        if (i < left.length && (j == right.length || !comp(left[i], right[j]))) {
            elems[k] = left[i];
            i += 1;
        } else {
            elems[k] = right[j];
            j += 1;
        }
        k += 1;
    }
}

namespace KeyWordSelect {
	[GtkTemplate (ui = "/com/github/liushiqi/MultipleSort/keyword_select.ui")]
	public class Window : Gtk.Window {
	    private File file;

	    private Row[] rows = {};
	    private string[] keys = {};

	    [GtkChild]
	    private Gtk.Window sort_result_window;

	    [GtkChild]
	    private Gtk.TextView sort_result;

	    [GtkChild]
	    private Gtk.ComboBoxText key_word_1;

	    [GtkChild]
	    private Gtk.ComboBoxText key_word_2;

	    [GtkChild]
	    private Gtk.ComboBoxText key_word_3;

	    [GtkChild]
	    private Gtk.ComboBoxText type_1;

	    [GtkChild]
	    private Gtk.ComboBoxText type_2;

	    [GtkChild]
	    private Gtk.ComboBoxText type_3;

	    [GtkCallback]
	    public bool result_destroy(Gdk.EventAny event) {
	        sort_result_window.hide();
	        debug("Result window hided.");
	        present();
	        return false;
	    }

	    [GtkCallback]
	    public void sort_cancel() {
	        close();
	        Gtk.Window window = new FileSelect.Window(this.application, file);
	        window.present();
	    }

	    [GtkCallback]
	    public void sort_confirm() {
	        int i = key_word_1.get_active(), j = key_word_2.get_active(), k = key_word_3.get_active();
	        int type_1 = this.type_1.get_active(), type_2 = this.type_2.get_active(), type_3 = this.type_3.get_active();
	        if (k != -1)
    	        merge_sort(rows, (a, b) => {
    	            if (type_3 == 0) return a.elems[k] < b.elems[k];
    	            else if (type_3 == 1) return int.parse(a.elems[k]) < int.parse(b.elems[k]);
    	            else return double.parse(a.elems[k]) < double.parse(b.elems[k]);
    	        });
    	    debug("Sort phase 1 finished.");
	        if (j != -1)
    	        merge_sort(rows, (a, b) => {
    	            if (type_2 == 0) return a.elems[j] < b.elems[j];
    	            else if (type_2 == 1) return int.parse(a.elems[j]) < int.parse(b.elems[j]);
    	            else return double.parse(a.elems[j]) < double.parse(b.elems[j]);
    	        });
    	    debug("Sort phase 2 finished.");
	        if (i != -1)
    	        merge_sort(rows, (a, b) => {
    	            if (type_1 == 0) return a.elems[i] < b.elems[i];
    	            else if (type_1 == 1) return int.parse(a.elems[i]) < int.parse(b.elems[i]);
    	            else return double.parse(a.elems[i]) < double.parse(b.elems[i]);
    	        });
    	    debug("Sort phase 3 finished.");
    	    string s = "";
            for (int index = 0; index < keys.length; ++index) {
                /*sort_result.insert_column(index);
                Gtk.Label label = new Gtk.Label(keys[index]);
                label.hexpand = false;
                label.halign = Gtk.Align.FILL;
                sort_result.attach(label, index, 0);*/
                s += keys[index] + "\t";
            }
            s += "\n";
            for (i = 0; i < rows.length; ++i) {
                //sort_result.insert_row(i);
                for (j = 0; j < keys.length; j++) {
                    s += rows[i].elems[j] + "\t";
                    //sort_result.attach(new Gtk.Label(rows[i].elems[j]), j, i + 1);
                }
                s += "\n";
            }
            sort_result.buffer.text = s;
            this.hide();
            sort_result_window.present();
	    }

		public Window(Gtk.Application app, File file) {
			Object(application: app);
			GLib.debug("File path: %s", file.get_path());
			this.file = file;
			FileInputStream stream;
			DataInputStream input;
			string str;
			try {
			    stream = file.read();
			    input = new DataInputStream(stream);
			    str = input.read_line();
			} catch (Error e) {
			    error("Why this happens?");
			}
			string[] tmp_keys = str.split(",");
			keys = {};
			foreach (var key in tmp_keys) {
			    if (key != null && key != "" && key != "\n" && key != "\t" && key != " " && key != "\xd") keys += key;
			}
			foreach (var key in keys) {
    			key_word_1.append(null, key);
	    	    key_word_2.append(null, key);
	    	    key_word_3.append(null, key);
			}
			while (true) {
			    try {
			        str = input.read_line();
			        if (str == null) break;
			        string[] elems = str.split(",");
			        string[] parsed_elems = {};
			        foreach (var elem in elems) if (elem != null && elem != "" && elem != "\n" && elem != "\t" && elem != " " && elem != "\xd") {
			            parsed_elems += elem;
			        }
			        rows += new Row(parsed_elems);
			    } catch (Error e) {
			        break;
			    }
			}
		}
	}
}
