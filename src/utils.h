#ifndef UTILS_H
#define UTILS_H

#include <gtk/gtk.h>
#include <stdarg.h>

// Row addition that handles all type conversions
void tv_add_row(GtkTreeView *treeview, ...) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    if (!GTK_IS_LIST_STORE(model)) return;

    GtkListStore *store = GTK_LIST_STORE(model);
    GtkTreeIter iter;
    va_list args;
    va_start(args, treeview);

    gint n_columns = gtk_tree_model_get_n_columns(model);
    gtk_list_store_append(store, &iter);

    for (gint i = 0; i < n_columns; i++) {
        GType col_type = gtk_tree_model_get_column_type(model, i);
        switch(col_type) {
            case G_TYPE_INT:    
                gtk_list_store_set(store, &iter, i, va_arg(args, int), -1); 
                break;
            case G_TYPE_STRING: 
                gtk_list_store_set(store, &iter, i, va_arg(args, char*), -1); 
                break;
            case G_TYPE_FLOAT:  
                gtk_list_store_set(store, &iter, i, va_arg(args, double), -1); 
                break;
        }
    }
    va_end(args);
}

// Auto-create columns for simple use cases
void tv_auto_create_columns(GtkTreeView *treeview, char **column_names) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    gint n_columns = gtk_tree_model_get_n_columns(model);

    for (gint i = 0; i < n_columns; i++) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            column_names[i] ? column_names[i] : "Column", 
            renderer, 
            "text", i, 
            NULL
        );
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}

// Simplified row removal functions
void tv_remove_selected(GtkTreeView *treeview) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    }
}

void tv_clear_rows(GtkTreeView *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    gtk_list_store_clear(GTK_LIST_STORE(model));
}

char* get_combo_box_text(GtkWidget* combo_box) {
    int active_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
    if (active_index == -1) return NULL;

    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_box));
    GtkTreeIter iter;
    
    if (gtk_tree_model_iter_nth_child(model, &iter, NULL, active_index)) {
        char *text;
        gtk_tree_model_get(model, &iter, 0, &text, -1);
        return text;
    }
    
    return NULL;
}

#endif // UTILS_H