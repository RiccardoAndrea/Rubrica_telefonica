#include "header.h"
GtkWidget *global_vbox_contatti = NULL;  // Definizione della variabile globale
stringa global_numero_telefonico;
stringa global_nome;
stringa global_cognome;

// Callback per il click sull'icona
void aggiungi_contatto(GtkWidget *widget, gpointer data) {
    
    gpointer *callback_data = (gpointer *)data;
    GtkApplication *app = GTK_APPLICATION(callback_data[0]);
    GtkWidget *main_window = GTK_WIDGET(callback_data[1]);

    GtkWidget *window; // finestra app
    GtkWidget *text_nome; // testo semplice nome
    GtkWidget *input_nome; // input nome
    GtkWidget *text_cognome; // testo semplice cognome
    GtkWidget *input_cognome; // input cognome
    GtkWidget *text_numero; // testo semplice numero
    GtkWidget *input_numero; // input numero
    GtkWidget *icon;// immagine icona
    GtkWidget * add_contact; // bottone per aggiungere contatto 
    GdkPixbuf *pixbuf;// Pixbuf per l'immagine
    GdkPixbuf *scaled_pixbuf;// ridimensionamento
    GtkWidget *vbox;// layout contenente i widget

   
    //creo nuova finestra
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Aggiungi Contatto");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Layout verticale
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    // aggiungo icona
    icon = gtk_image_new_from_file("immagini/contatto_icon.png");
    gtk_style_context_add_class(gtk_widget_get_style_context(icon), "icon-button");  
    gtk_widget_set_size_request(icon, 100, 100);//riserva spazio
    gtk_box_pack_start(GTK_BOX(vbox), icon, FALSE, FALSE, 0);


    text_nome = gtk_label_new("Nome");
    gtk_style_context_add_class(gtk_widget_get_style_context(text_nome), "title-label");
    input_nome = gtk_entry_new();
    text_cognome = gtk_label_new("Cognome");
    gtk_style_context_add_class(gtk_widget_get_style_context(text_cognome), "title-label");
    input_cognome = gtk_entry_new();
    text_numero = gtk_label_new("Numero");
    gtk_style_context_add_class(gtk_widget_get_style_context(text_numero), "title-label");
    input_numero = gtk_entry_new();
   // spacer = gtk_label_new("");


    //icona in bottone ridimensionata
    pixbuf = gdk_pixbuf_new_from_file("immagini/plus_icon.png", NULL);
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 82, 82, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(scaled_pixbuf);
    add_contact = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(add_contact), GTK_RELIEF_NONE);
    gtk_container_add(GTK_CONTAINER(add_contact), icon);
   
    

    
    // aggiungi al vbox i vari Widget
    gtk_box_pack_start(GTK_BOX(vbox), text_nome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_nome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_cognome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_cognome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_numero, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), input_numero, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), add_contact, FALSE, FALSE, 0);
    

    // Aggiungi il layout alla finestra
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //mostra finestra
    gtk_widget_show_all(window);/* MODIFICA: CREAZIONE DELLA STRUCT PER PASSARE I WIDGET AGGIORNATI */
    ContactData *cd = g_malloc(sizeof(ContactData));
    cd->input_nome = input_nome;
    cd->input_cognome = input_cognome;
    cd->input_numero = input_numero;
    cd->vbox = vbox;
    cd->main_window = main_window; // AGGIUNTA: PASSIAMO LA FINESTRA PRINCIPALE

    g_signal_connect(add_contact, "clicked", G_CALLBACK(contatto_aggiunto), cd);
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
    GtkWidget *scrolled_window; // finestra scrilled
    GtkWidget *vbox_scroll; // contenitore widget scrollbar
    GtkWidget * titolo;
    archivio_telefonico rubrica;
    

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Rubrica Telefonica");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    
    // Carica il CSS
    GtkCssProvider *provider;
    GdkScreen *screen;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider); // Libera la memoria del provider

 
    
    // Crea un contenitore GtkFixed per posizionamento assoluto
    fixed = gtk_fixed_new();

    //barra di ricerca
    aggiungi_barra_ricerca(fixed,window);  

    // Carica l'immagine da file come pixbuf
    pixbuf = gdk_pixbuf_new_from_file("immagini/aggiungi_icon.png", NULL);

    // Ridimensiona l'immagine (es 62 x 62)
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 35, 35, GDK_INTERP_BILINEAR);

    // Crea un GtkImage dal pixbuf ridimensionato
    icon = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // creo un bottone
    icon_button = gtk_button_new();
    
    gtk_style_context_add_class(gtk_widget_get_style_context(icon_button), "icon-button");  
    // setto il bordo
    gtk_button_set_relief(GTK_BUTTON(icon_button), GTK_RELIEF_NONE); // nessun bordo

    // aggiungo l'immagine al bottone attraverso un container
    gtk_container_add(GTK_CONTAINER(icon_button), icon);

    // Collega il segnale "clicked" al callback
    gpointer *callback_data = g_malloc(sizeof(gpointer) * 2);
    callback_data[0] = app;
    callback_data[1] = window; // passiamo anche la finestra principale
    g_signal_connect(icon_button, "clicked", G_CALLBACK(aggiungi_contatto), callback_data);


    // Posiziona il pulsante in alto a destra
    gtk_fixed_put(GTK_FIXED(fixed), icon_button, 490, 5); 

    //aggiungi contenitore alla finestra
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //crea uno scroll bar
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_style_context_add_class(gtk_widget_get_style_context(scrolled_window), "scrolled-window");

    //setta lo scrollbar se gli elementi suerano la dimensione della finestra attiva
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // responsive se alalrghi la finestra in orizzontale e verticale
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_widget_set_hexpand(scrolled_window, TRUE);


    //creo contenitore per i widget 
    vbox_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    //creo titolo
    titolo = gtk_label_new("Contatti");
    const char *markup = "<span font_desc='Sans 16'>Contatti</span>";
    gtk_label_set_markup(GTK_LABEL(titolo), markup);
    gtk_style_context_add_class(gtk_widget_get_style_context(titolo), "title-label");
    gtk_container_add(GTK_CONTAINER(vbox_scroll), titolo);

    // Salva il contenitore globale (lo useremo per aggiornare la lista dei contatti)
    global_vbox_contatti = vbox_scroll;
    
    //leggo i contatti
    rubrica.n=0;
    leggi_contatti("contatti.txt", &rubrica);
    const int n = rubrica.n;
    g_print("Numero di contatti: %d\n", rubrica.n);
    
    if (n == 0) {
        // Aggiungi un messaggio che indica che non ci sono contatti
        GtkWidget *no_contacts_label = gtk_label_new("Nessun contatto disponibile.");
        gtk_style_context_add_class(gtk_widget_get_style_context(no_contacts_label), "title-label");
        gtk_container_add(GTK_CONTAINER(vbox_scroll), no_contacts_label);
    }
    for (int i = 0; i < n; i++) {
        char label[100];
        strcpy(label, rubrica.nome[i]);  // Copia il nome in label
  
        strcat(label, " ");              // Aggiungi uno spazio tra nome e cognome
        strcat(label, rubrica.cognome[i]); // Aggiungi il cognome    
        GtkWidget *button = gtk_button_new_with_label(label);
        gtk_style_context_add_class(gtk_widget_get_style_context(button), "contact-button");
        gtk_container_add(GTK_CONTAINER(vbox_scroll), button);
    
        // Alloca un nuovo blocco di memoria per il callback (per ogni bottone)
        gpointer *callback_data2 = g_malloc(sizeof(gpointer) * 5);
        callback_data2[0] = app;
        callback_data2[1] = window; // passiamo anche la finestra principale
        callback_data2[2] = g_strdup(rubrica.nome[i]);  
        callback_data2[3] = g_strdup(rubrica.cognome[i]);  
        callback_data2[4] = g_strdup(rubrica.numero_telefonico[i]);  

        // Collega il segnale "clicked" al callback
        g_signal_connect_data(button, "clicked", G_CALLBACK(on_button_clicked),
                                callback_data2, NULL, 0); // Rimuovi g_free dalla closure notify
    }
    
    //aggiungo il contenitore allo scroll
    gtk_container_add(GTK_CONTAINER(scrolled_window), vbox_scroll);

    gtk_widget_set_size_request(scrolled_window, 400, 300); 
    {
        gint window_width, window_height;
        gtk_window_get_size(GTK_WINDOW(window), &window_width, &window_height);
        gint scrolled_width, scrolled_height;
        gtk_widget_get_size_request(scrolled_window, &scrolled_width, &scrolled_height);
        gint x_position = (window_width - scrolled_width) / 2;
        gint y_position = (window_height - scrolled_height) / 2;
        gtk_fixed_put(GTK_FIXED(fixed), scrolled_window, x_position, y_position);
    }

    //mostra finestra
    gtk_widget_show_all(window);

    // Libera la memoria dei pixbuf
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
}

void contatto_aggiunto(GtkWidget *widget, gpointer data) {

    // Ottieni GtkApplication dalla finestra principale
    GtkWidget *parent_window = gtk_widget_get_toplevel(widget);
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(parent_window));

    ContactData *cd = (ContactData *)data;

 
    const char *nome = gtk_entry_get_text(GTK_ENTRY(cd->input_nome));
    const char *cognome = gtk_entry_get_text(GTK_ENTRY(cd->input_cognome));
    const char *numero = gtk_entry_get_text(GTK_ENTRY(cd->input_numero));

    if (g_strcmp0(nome, "") == 0 || g_strcmp0(cognome, "") == 0 || g_strcmp0(numero, "") == 0) {
        
        GtkWidget *parent_window = gtk_widget_get_toplevel(widget);
        if (GTK_IS_WINDOW(parent_window)) {
         
            GtkWidget *container = cd->vbox;
            GtkWidget *error_label = gtk_label_new(NULL);
            gtk_label_set_markup(GTK_LABEL(error_label), "<span foreground='red'>INSERIRE CONTATTI OBBLIGATORI</span>");
            gtk_box_pack_end(GTK_BOX(container), error_label, FALSE, FALSE, 5); // AGGIUNTA LABEL DI ERRORE
            gtk_widget_show_all(parent_window);
        }
    } else {
        g_print("Contatto aggiunto: %s %s - %s\n", nome, cognome, numero);
        archivio_telefonico rubrica;
        leggi_contatti("contatti.txt", &rubrica);
        if (inserisci_elemento(&rubrica, nome, cognome, numero) == 1) {
            printf("Contatto inserito con successo.\n");
            printf("\n\n");
        } else {
            printf("Memoria piena! Impossibile aggiungere il contatto.\n");
        }
        GtkWidget *parent_window = gtk_widget_get_toplevel(widget);
        gtk_window_close(GTK_WINDOW(parent_window)); // CHIUDI LA FINESTRA
        gtk_window_close(GTK_WINDOW(cd->main_window)); // ***CHIUSURA FINESTRA PRINCIPALE***

        create_window(app); // Creiamo una nuova finestra con l'app

    }
}

void on_button_clicked(GtkButton *button, gpointer user_data) {
    GtkApplication * app; //app data
    GtkWidget *text_numero; // testo semplice numero
    GtkWindow *main_window;// finestra main app
    GtkWidget * window; // nuova finestra
    gpointer *callback_data;// tipo gpointer utile a recuperare le info passate user_data
    GtkWidget *icon_telefono; // tipo base per qualsiasi elemento visibile nell'app.
    GtkWidget *icon_cestino; // icona cestino
    GtkWidget *fixed;   // Contenitore GtkFixed per il posizionamento assoluto
    GtkWidget *icon_button_telefono;// bottone
    GtkWidget *icon_button_cestino;// bottone
    GdkPixbuf *pixbuf;// Pixbuf per l'immagine
    GdkPixbuf *pixbuf2;
    GdkPixbuf *scaled_pixbuf;// ridimensionamento
    GdkPixbuf *scaled_pixbuf2;
    
    // apriamo la nuova finestra grazie alla calback passata
    callback_data = (gpointer *)user_data;
    main_window = (GtkWindow *)callback_data[1];
    app = (GtkApplication *)callback_data[0];
    char* nome = callback_data[2];  // Nome
    char* cognome = callback_data[3];  // Cognome
    char* numero_telefonico = callback_data[4];  // Numero telefonico  
    // Salva i dati nelle variabili globali
    printf("il nome  e; %s\n",nome);
    strcpy(global_nome, nome);
    strcpy(global_cognome, cognome);
    strcpy(global_numero_telefonico, numero_telefonico);
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Info Contatto");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    const char * numero = global_numero_telefonico;
    text_numero = gtk_label_new(numero);
    gtk_style_context_add_class(gtk_widget_get_style_context(text_numero), "title-label");
    gtk_label_set_xalign(GTK_LABEL(text_numero), 0.5); // Centra orizzontalmente
    gtk_label_set_yalign(GTK_LABEL(text_numero), 0.5); // Centra verticalmente


    // Crea un contenitore GtkFixed per posizionamento assoluto
    fixed = gtk_fixed_new();

    // Posiziona il label nel fixed
    gtk_fixed_put(GTK_FIXED(fixed), text_numero, 150, 150);  

    // Carica l'immagine da file come pixbuf
    pixbuf = gdk_pixbuf_new_from_file("immagini/telefono_icon.png", NULL);
    pixbuf2 = gdk_pixbuf_new_from_file("immagini/cestino_icon.jpg", NULL);

    // Ridimensiona l'immagine (es 62 x 62)
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 45, 45, GDK_INTERP_BILINEAR);
    scaled_pixbuf2 = gdk_pixbuf_scale_simple(pixbuf2, 45, 45, GDK_INTERP_BILINEAR);

    // Crea un GtkImage dal pixbuf ridimensionato
    icon_telefono = gtk_image_new_from_pixbuf(scaled_pixbuf);
    icon_cestino = gtk_image_new_from_pixbuf(scaled_pixbuf2);

    // creo un bottone
    icon_button_telefono = gtk_button_new();
    icon_button_cestino = gtk_button_new();

    // setto il bordo
    gtk_button_set_relief(GTK_BUTTON(icon_button_telefono), GTK_RELIEF_NONE); // nessun bordo
    gtk_button_set_relief(GTK_BUTTON(icon_button_cestino), GTK_RELIEF_NONE); 

    // aggiungo l'immagine al bottone attraverso un container
    gtk_container_add(GTK_CONTAINER(icon_button_telefono), icon_telefono);
    gtk_container_add(GTK_CONTAINER(icon_button_cestino), icon_cestino);

    // Posiziona il pulsante in alto a destra
    gtk_fixed_put(GTK_FIXED(fixed), icon_button_telefono, 270, 150); 
    gtk_fixed_put(GTK_FIXED(fixed), icon_button_cestino, 320, 150); 

    //aggiungi contenitore alla finestra
    gtk_container_add(GTK_CONTAINER(window), fixed);

    gtk_widget_show_all(window);


    g_signal_connect(icon_button_telefono, "clicked", G_CALLBACK(inoltra_chiamata), NULL);

    g_signal_connect(icon_button_cestino, "clicked", G_CALLBACK(cancella_contatto), main_window);

    g_print("Il bottone è stato cliccato!\n");
   
}

void aggiungi_barra_ricerca(GtkWidget *fixed, GtkWidget *main_window) {
    GtkWidget *search_bar;  // Barra di ricerca
    GtkWidget *search_icon; // Icona della lente di ingrandimento
    GtkWidget *hbox;        // Contenitore orizzontale per l'icona e la barra di ricerca
    GtkWidget *icon_button; // Bottone per l'icona

    // Crea una GtkEntry per la barra di ricerca
    search_bar = gtk_entry_new();
    gtk_widget_set_size_request(search_bar, 350, 30); // Dimensione della barra di ricerca

    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("immagini/lente_ricerca.png", &error);
    if (!pixbuf) {
        g_printerr("Errore nel caricamento dell'immagine: %s\n", error->message);
        g_error_free(error);
        return;
    }
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 20, 20, GDK_INTERP_BILINEAR);
    search_icon = gtk_image_new_from_pixbuf(scaled_pixbuf);
    
    // Crea il bottone per l'icona
    icon_button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(icon_button), search_icon); // Aggiungi l'icona al bottone

    // Aggiungi l'icona e la barra di ricerca in un contenitore orizzontale
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Spaziatura tra l'icona e la barra di ricerca
    gtk_box_pack_start(GTK_BOX(hbox), icon_button, FALSE, FALSE, 0); // Aggiungi l'icona
    gtk_box_pack_start(GTK_BOX(hbox), search_bar, TRUE, TRUE, 0);   // Aggiungi la barra di ricerca

    // Posiziona la barra di ricerca e l'icona nel contenitore GtkFixed
    gtk_fixed_put(GTK_FIXED(fixed), hbox, 50, 10); // Modifica le coordinate per la posizione

    // Collega un segnale di ricerca E PASSA il main window
    g_signal_connect(search_bar, "changed", G_CALLBACK(ricerca_contatti), main_window);
}

void ricerca_contatti(GtkEntry *entry, gpointer user_data) 
{
    // Recupera la finestra principale dal parametro user_data
    GtkWidget *main_window = GTK_WIDGET(user_data);
    // Recupera l'applicazione dalla finestra
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(main_window));
    // ***ESTRAIAMO IL TESTO INSERITO NEL CAMPO DI RICERCA***
    const char *text = gtk_entry_get_text(entry);
    archivio_telefonico rubrica;
    rubrica.n = 0;
    if (strlen(text) == 0) {
        if (global_vbox_contatti) {
            // Rimuovi tutti i figli attuali
            GList *children = gtk_container_get_children(GTK_CONTAINER(global_vbox_contatti));
            for (GList *iter = children; iter != NULL; iter = iter->next) {
                gtk_widget_destroy(GTK_WIDGET(iter->data));
            }
            g_list_free(children);
        }
        leggi_contatti("contatti.txt", &rubrica);
        const int n = rubrica.n;
        g_print("Numero di contatti: %d\n", rubrica.n);
        
        for (int i = 0; i < n; i++) {
            char label[100];
            strcpy(label, rubrica.nome[i]);  // Copia il nome in label
      
            strcat(label, " ");              // Aggiungi uno spazio tra nome e cognome
            strcat(label, rubrica.cognome[i]); // Aggiungi il cognome    
            GtkWidget *button = gtk_button_new_with_label(label);
            gtk_style_context_add_class(gtk_widget_get_style_context(button), "contact-button");
            gtk_container_add(GTK_CONTAINER(global_vbox_contatti), button);  
            gpointer *callback_data2 = g_malloc(sizeof(gpointer) * 5);
            callback_data2[0] = app;
            callback_data2[1] = main_window; // passiamo anche la finestra principale
            callback_data2[2] = g_strdup(rubrica.nome[i]);  
            callback_data2[3] = g_strdup(rubrica.cognome[i]);  
            callback_data2[4] = g_strdup(rubrica.numero_telefonico[i]);  
    
            // Collega il segnale "clicked" al callback
            g_signal_connect_data(button, "clicked", G_CALLBACK(on_button_clicked),
                                    callback_data2, NULL, 0); // Rimuovi g_free dalla closure notify
        }
         // Mostra il contenitore aggiornato
         gtk_widget_show_all(global_vbox_contatti);
    } 
    else{
        g_print("Ricerca per: %s\n", text);
        leggi_contatti("contatti.txt", &rubrica);
        int n = rubrica.n, indice_i = -1;
        size_t distanza, min = SIZE_MAX;
        for(int i = 0; i < n; i++)
        {
            distanza = levenshtein(text, rubrica.nome[i]);
            if (distanza < min)
            {
                min = distanza;
                indice_i = i;
            }
            
            
        }
        if (indice_i != -1) {
            g_print("trovato: %s\n", rubrica.nome[indice_i]);
            
            // Se abbiamo un contenitore globale, lo puliamo e vi aggiungiamo il bottone trovato
            if (global_vbox_contatti) {
                // Rimuovi tutti i figli attuali
                GList *children = gtk_container_get_children(GTK_CONTAINER(global_vbox_contatti));
                for (GList *iter = children; iter != NULL; iter = iter->next) {
                    gtk_widget_destroy(GTK_WIDGET(iter->data));
                }
                g_list_free(children);
                
                // Crea il bottone con il contatto trovato
                char label[100];
                snprintf(label, sizeof(label), "%s %s", rubrica.nome[indice_i], rubrica.cognome[indice_i]);
                GtkWidget *button = gtk_button_new_with_label(label);
                gtk_container_add(GTK_CONTAINER(global_vbox_contatti), button);
                
                gpointer *callback_data2 = g_malloc(sizeof(gpointer) * 5);
                callback_data2[0] = app;
                callback_data2[1] = main_window; // passiamo anche la finestra principale
                callback_data2[2] = g_strdup(rubrica.nome[indice_i]);  
                callback_data2[3] = g_strdup(rubrica.cognome[indice_i]);  
                callback_data2[4] = g_strdup(rubrica.numero_telefonico[indice_i]);  
        
                // Collega il segnale "clicked" al callback
                g_signal_connect_data(button, "clicked", G_CALLBACK(on_button_clicked),
                                        callback_data2, NULL, 0); // Rimuovi g_free dalla closure notify
            
                // Mostra il contenitore aggiornato
                gtk_widget_show_all(global_vbox_contatti);
            }
        }
   
    }
    
}

void inoltra_chiamata(GtkWidget *widget, gpointer data)
{
    archivio_telefonico rubrica;
    leggi_contatti("contatti.txt", &rubrica);
    if(chiamata(&rubrica,global_nome, global_cognome)){
        g_print("chiamata effettuata\n");
        int num_chiamate = trova_chiamate(&rubrica, global_numero_telefonico);
        if (num_chiamate >= 0) {
            printf("Numero di chiamate: %d\n", num_chiamate);
            printf("\n\n");
        } 
        else {
            printf("Numero non trovato.\n");
            printf("\n\n");
        }
    }
    else
        g_print("numero non raggiungibile\n");

    
            
}

void cancella_contatto(GtkWidget *widget, gpointer data)
{
    // Recupera la finestra principale dal parametro user_data
    GtkWidget *main_window = GTK_WIDGET(data);
    // Recupera l'applicazione dalla finestra
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(main_window));
    //parente finestra
    GtkWidget *parent_window = gtk_widget_get_toplevel(widget);
    archivio_telefonico rubrica;
    leggi_contatti("contatti.txt", &rubrica);
    if (cancella_numero(&rubrica, global_nome, global_cognome) == 1) {
        printf("Contatto cancellato con successo.\n");
        printf("\n\n");
       
        
    } else {
        printf("Contatto non trovato.\n");
        printf("\n\n");
    }
    gtk_window_close(GTK_WINDOW(parent_window)); // CHIUDI LA FINESTRA
    gtk_window_close(GTK_WINDOW(main_window));
    create_window(app);
}



