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

public class Row {
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

	    [GtkChild]
	    private Gtk.ComboBoxText order_1;

	    [GtkChild]
	    private Gtk.ComboBoxText order_2;

	    [GtkChild]
	    private Gtk.ComboBoxText order_3;

	    [GtkCallback]
	    public void sort_cancel() {
	        close();
	        Gtk.Window window = new FileSelect.Window(this.application, file);
	        window.present();
	    }

	    bool compare(Row a, Row b, int key_word, int type, int order) {
	        if (type == 0) {
	            if (order == 0)
	                return a.elems[key_word] > b.elems[key_word];
	            else
	                return a.elems[key_word] < b.elems[key_word];
	        } else if (type == 1) {
	            if (order == 0)
	                return int.parse(a.elems[key_word]) > int.parse(b.elems[key_word]);
	            else
	                return int.parse(a.elems[key_word]) < int.parse(b.elems[key_word]);
	        } else {
	            if (order == 0)
	                return double.parse(a.elems[key_word]) > double.parse(b.elems[key_word]);
	            else
	                return double.parse(a.elems[key_word]) < double.parse(b.elems[key_word]);
	        }
	    }
	    
	    bool equal(Row a, Row b, int key_word) {
	        return a.elems[key_word] == b.elems[key_word];
	    }

	    public void inner_sort() {
	        int i = key_word_1.get_active(), j = key_word_2.get_active(), k = key_word_3.get_active();
	        int type_1 = this.type_1.get_active(), type_2 = this.type_2.get_active(), type_3 = this.type_3.get_active();
	        int order_1 = this.order_1.get_active(), order_2 = this.order_2.get_active(), order_3 = this.order_3.get_active();
	        merge_sort(rows, (a, b) => {
	            if (i == -1 || equal(a, b, i)) {
	                if (j == -1 || equal(a, b, j)) {
	                    if (k != -1)
    	                    return compare(a, b, k, type_3, order_3);
    	                else return true;
	                } else
	                    return compare(a, b, j, type_2, order_2);
	            } else {
	                return compare(a, b, i, type_1, order_1);
	            }
	        });
	    }

	    [GtkCallback]
	    public void sort_confirm() {
            var begin = new DateTime.now_local();
	        this.inner_sort();
            var end = new DateTime.now_local();
    	    string s = "";
            for (int index = 0; index < keys.length; ++index) {
                s += keys[index] + ",";
            }
            s += "\n";
            for (int i = 0; i < rows.length; ++i) {
                for (int j = 0; j < keys.length; j++) {
                    s += rows[i].elems[j] + ",";
                }
                s += "\n";
            }
            this.hide();
            Gtk.Window window = new SortResult.Window(this.application, file, s, end.difference(begin));
	        window.present();
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

namespace SortResult {
	[GtkTemplate (ui = "/com/github/liushiqi/MultipleSort/sort_result.ui")]
    public class Window : Gtk.Window {
        private string file_result;
        private File file;

        [GtkChild]
        Gtk.Label sort_result;

        [GtkCallback]
        void close_clicked() {
	        close();
	        Gtk.Window window = new KeyWordSelect.Window(this.application, file);
	        window.present();
        }

        [GtkCallback]
        void save_confirmed() {
            var file_save = new Gtk.FileChooserDialog(null, this, Gtk.FileChooserAction.SAVE);
            file_save.add_button("_Cancel", Gtk.ResponseType.CANCEL);
            file_save.add_button("_Save", Gtk.ResponseType.OK);
            file_save.set_do_overwrite_confirmation(true);
            if (file_save.run() != Gtk.ResponseType.OK) {
                file_save.destroy();
                return;
            }
            try {
                File write_to = file_save.get_file();
                DataOutputStream file = null;
                if (write_to.query_exists())
                    file = new DataOutputStream(write_to.replace(null, false, FileCreateFlags.NONE));
                else
                    file = new DataOutputStream(write_to.create(FileCreateFlags.NONE));
                file.put_string(file_result);
            } catch(Error e) {
                error("%s\n", e.message);
            }
            file_save.destroy();
        }

        public Window(Gtk.Application app, File file, string s, TimeSpan timeused) {
            Object(application: app);
            this.file = file;
            this.file_result = s;
            var screen = this.get_screen ();
            
            var css_provider = new Gtk.CssProvider();
            try {
                css_provider.load_from_data("""label#sort-time {
                                                 font: 40px Sans;
                                               }""");
                Gtk.StyleContext.add_provider_for_screen(screen, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_USER);
            } catch (Error e) {
                error("css load error");
            }
            
            sort_result.label = @"Time used $(timeused / 1000 / 60):$(timeused / 1000 % 60).$(timeused % 1000)";
        }
    }
}
