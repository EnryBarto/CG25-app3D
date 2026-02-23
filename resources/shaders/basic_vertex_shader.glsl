#version 330 core

layout (location = 0) in vec3 aPos;   // Posizione presa dal layer 0 del VAO
layout (location = 1) in vec4 aColor; // Colore preso dal layer 1 del VAO

out vec4 vertexColor;       // Colore elaborato da questa shader

// Variabili uniform settate dal programma principale, rimangono le stesse per ogni frammento di uno stesso ciclo di rendering
uniform mat4 Projection;    // Matrice di proiezione
uniform mat4 Model;         // Matrice di modellazione
uniform mat4 View;          // Matrice di Vista

void main() {
    /* Trasformazione dei vertici dalle coordinate nel sistema di riferimento dell'oggetto (apos),
     * al sistema di riferimento del mondo (premoltiplicazione per Model) e successivamente proiettate
     * nel cubo di centro l'origine e lato lungo 2, con x,y,z che variano tra -1 ed 1- (premoltiplicazione per la matrice Projection)
     */
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    vertexColor = aColor; // Impostiamo il colore come letto dal VBO
}

