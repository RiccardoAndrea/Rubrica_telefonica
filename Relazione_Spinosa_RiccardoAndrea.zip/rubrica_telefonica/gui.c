#include "header.h"


// Callback per il click sull'icona
void aggiungi_contatto(GtkWidget *widget, gpointer data) {
    
    GtkApplication *app = GTK_APPLICATION(data);
    GtkWidget *window; // finestra app
    GtkWidget *text_nome; // testo semplice nome
    GtkWidget *input_nome; // input nome
    GtkWidget *text_cognome; // testo semplice cognome
    GtkWidget *input_cognome; // input cognome
    GtkWidget *text_numero; // testo semplice numero
    GtkWidget *input_numero; // input numero
    GtkWidget *icon;// immagine icona
    GtkWidget * add_contact; // bottone per aggiungere contatto 
    GtkWidget *spacer; // spazio vuoto 
    GdkPixbuf *pixbuf;// Pixbuf per l'immagine
    GdkPixbuf *scaled_pixbuf;// ridimensionamento
    GtkWidget *vbox;// layout contenente i widget

   
    //creo nuova finestra
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Aggiungi Contatto");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    // Layout verticale
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    // aggiungo icona
    icon = gtk_image_new_from_file("immagini/contatto_icon.png");
    gtk_widget_set_size_request(icon, 100, 100);//riserva spazio
    gtk_box_pack_start(GTK_BOX(vbox), icon, FALSE, FALSE, 0);


    text_nome = gtk_label_new("Nome");
    input_nome = gtk_entry_new();
    text_cognome = gtk_label_new("Cognome");
    input_cognome = gtk_entry_new();
    text_numero = gtk_label_new("Numero");
    input_numero = gtk_entry_new();
    spacer = gtk_label_new("");


    //icona in bottone ridimensionata
    pixbuf = gdk_pixbuf_new_from_file("immagini/plus_icon.png", NULL);
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 82, 82, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(scaled_pixbuf);
    add_contact = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(add_contact), GTK_RELIEF_NONE);
    gtk_container_add(GTK_CONTAINER(add_contact), icon);
    g_signal_connect(add_contact, "clicked", G_CALLBACK(contatto_aggiunto), data);
    
    // ridimensiona lo spazio vuoto
    gtk_widget_set_size_request(spacer, -1, 20); // larghezza -1 (default), altezza 20px
    
    // aggiungi al vbox i vari Widget
    gtk_box_pack_start(GTK_BOX(vbox), text_nome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_nome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_cognome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_cognome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_numero, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_numero, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), spacer, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), add_contact, FALSE, FALSE, 0);
    

    // Aggiungi il layout alla finestra
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //mostra finestra
    gtk_widget_show_all(window);
}

// crea una nuova finestra
void create_window(GtkApplication *app) {
    //dichiaro le variabili gtk
    GtkWidget * window; // finestra app
    GtkWidget *icon; // tipo base per qualsiasi elemento visibile nell'app.
    GtkWidget *fixed;   // Contenitore GtkFixed per il posizionamento assoluto
    GtkWidget *icon_button;// bottone
    GdkPixbuf *pixbuf;// Pixbuf per l'immagine
    GdkPixbuf *scaled_pixbuf;// ridimensionamento

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Rubrica Telefonica");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    // Crea un contenitore GtkFixed per posizionamento assoluto
    fixed = gtk_fixed_new();

    // Carica l'immagine da file come pixbuf
    pixbuf = gdk_pixbuf_new_from_file("immagini/aggiungi_icon.png", NULL);

    // Ridimensiona l'immagine (es 62 x 62)
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 62, 62, GDK_INTERP_BILINEAR);

    // Crea un GtkImage dal pixbuf ridimensionato
    icon = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // creo un bottone
    icon_button = gtk_button_new();

    // setto il bordo
    gtk_button_set_relief(GTK_BUTTON(icon_button), GTK_RELIEF_NONE); // nessun bordo

    // aggiungo l'immagine al bottone attraverso un container
    gtk_container_add(GTK_CONTAINER(icon_button), icon);

    // Collega il segnale "clicked" al callback
    g_signal_connect(icon_button, "clicked", G_CALLBACK(aggiungi_contatto), app);

    // Posiziona il pulsante in alto a destra
    gtk_fixed_put(GTK_FIXED(fixed), icon_button, 490, 10); 

    //aggiungi contenitore alla finestra
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //mostra finestra
    gtk_widget_show_all(window);

    // Libera la memoria dei pixbuf
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
}

void contatto_aggiunto(GtkWidget *widget, gpointer data) {
    GtkWidget *parent_window;//parente vecchia finestra
     parent_window = gtk_widget_get_toplevel(widget);
     gtk_widget_destroy(parent_window);
 
    g_print("Contatto aggiunto!\n");
}

void on_back_passed(GtkWidget *widget, gpointer data) {
    // esempio minimo
    g_print("Torno indietro!\n");
}