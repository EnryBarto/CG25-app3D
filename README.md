# Progetto 2 - Computer Graphics - A.A. 2025/26

## Sviluppo di un'app interattiva 3D

### Obiettivi:

- Sviluppare un'applicazione grafica in C++ che sfrutti le potenzialità di OpenGL e della pipeline di rendering programmabile, e faccia uso della libreria ImGUI per la personalizzazione, con l'obiettivo di creare un ambiente 3D interattivo e immersivo.

### Requisiti tecnici:

- **Modellazione**:
    - Creazione di geometrie complesse assemblando primitive geometriche di base (cubo, piramide, sfera, cilindro, cono, toro).
    - Importazione di modelli 3D esterni in formato .obj, garantendo la corretta gestione dei materiali associati (file .mtl).

- **Interazione**:
    - **Selezione**: Permettere all'utente di selezionare individualmente gli oggetti mediante un clic del mouse. Visualizzare sulla Gui il nome dell’oggetto selezionato.
    - **Modifica**: L'utente potrà personalizzare l'aspetto degli oggetti selezionati accedendo a un menu contestuale. Questo menu permetterà di:
        - Modificare il **materiale**: Per le primitive di base, sarà possibile cambiare il materiale dell'oggetto tra un insieme di materiali base.
        - Scegliere lo **shader**: Sia per le primitive di base che per i modelli importati, sarà possibile selezionare diversi shader (tra quelli specificati successivamente nella sezione Illuminazione) per ottenere effetti visivi differenti.

- **Navigazione**: Implementare un sistema di navigazione basato sia sul trackball, che sulla modifica della direzione della camera mediante il movimento passivo del mouse sulla finestra,  combinato con i comandi WASD per spostarsi liberamente all'interno della scena.

- **Illuminazione**:
    - Prevedere la presenza di due luci puntiformi nella scena, delle quali si possono modificare le posizioni nel mondo mediante interfaccia imGUI.
    - Modelli di illuminazione: Implementare i modelli di Phong e Blinn-Phong, utilizzando entrambe le tecniche di shading interpolativo e Phong.

- **Texture**:
    - **Applicazione di texture**: Permettere di applicare texture alle primitive geometriche.

- **Effetti**:
    - **Cubemap**: Integrare una cubemap per simulare un ambiente circostante e creare effetti di riflessione realistici.

- **Gestione delle collisioni**:
    - **Collisioni con la telecamera**: Implementare un sistema di rilevamento delle collisioni tra la telecamera e gli oggetti della scena, evitando che la telecamera penetri all'interno degli oggetti.

- **Animazioni**:
    - Implementare animazioni degli oggetti della scena.
