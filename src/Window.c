#include "Window.h"

#include <gtk4-layer-shell.h>

#include "Option/Option.h"
#include "glib.h"

static const char *const gtk_window_style =
    "window { background-color: rgba(0, 0, 0, 0); }";

static const char *const markup_fmtstr =
    "<span foreground=\"#%02X%02X%02X%02X\">"
    "<span font_family=\"%s\" %s size=\"%ld\">%s</span>\n"
    "<span font_family=\"%s\" %s size=\"%ld\">%s</span>"
    "</span>";

void app_activate(GtkApplication *app, gpointer user_data) {
  auto popt = (const Option *)user_data;

  auto win = gtk_application_window_new(app);
  auto gwin = GTK_WINDOW(win);
  gtk_window_set_default_size(gwin, popt->hshift, popt->vshift);
  gtk_layer_init_for_window(gwin);
  gtk_layer_set_layer(gwin, GTK_LAYER_SHELL_LAYER_OVERLAY);
  gtk_layer_set_monitor(gwin, nullptr);
  gtk_layer_set_anchor(gwin, GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
  gtk_layer_set_anchor(gwin, GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);
  gtk_layer_set_margin(gwin, GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
  gtk_layer_set_margin(gwin, GTK_LAYER_SHELL_EDGE_RIGHT, 0);
  gtk_layer_set_exclusive_zone(gwin, 0);
  gtk_layer_set_keyboard_mode(gwin, GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);

  auto pvd = gtk_css_provider_new();
  gtk_css_provider_load_from_string(pvd, gtk_window_style);
  gtk_style_context_add_provider_for_display(
      gdk_display_get_default(), GTK_STYLE_PROVIDER(pvd),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  auto lab = gtk_label_new(NULL);
  auto glab = GTK_LABEL(lab);

  gtk_widget_set_halign(lab, GTK_ALIGN_START);
  gtk_widget_set_valign(lab, GTK_ALIGN_START);
  gtk_label_set_use_markup(glab, TRUE);

  auto esctext1 = g_markup_escape_text(popt->text1, -1);
  auto esctext2 = g_markup_escape_text(popt->text2, -1);

  auto markup = g_strdup_printf(
      markup_fmtstr, popt->rgba.r, popt->rgba.g, popt->rgba.b, popt->rgba.a,
      popt->font1, get_markup_from_style(popt->style1),
      (uint64_t)(18 * 1024 * popt->scale), popt->text1, popt->font2,
      get_markup_from_style(popt->style2), (uint64_t)(12 * 1024 * popt->scale),
      popt->text2);
  g_free(esctext1);
  g_free(esctext2);

  /*
    auto markup = g_markup_printf_escaped(
        markup_fmtstr, popt->rgba.r, popt->rgba.g, popt->rgba.b, popt->rgba.a,
        popt->font1, get_markup_from_style(popt->style1),
        (uint64_t)(18 * 1024 * popt->scale), popt->text1, popt->font2,
        get_markup_from_style(popt->style2), (uint64_t)(12 * 1024 *
                                                        popt->scale),
    popt->text2);
  */
  gtk_label_set_markup(glab, markup);
  g_free(markup);

  gtk_window_set_child(gwin, lab);
  gtk_window_present(gwin);
}
