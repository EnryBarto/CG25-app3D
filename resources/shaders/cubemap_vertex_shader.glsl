#version 330 core
layout (location = 0) in vec3 aPos;   // Attributo Posizione
uniform mat4 Projection;  //vARIABILE DI TIPO uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 View;

 out vec3 TexCoords;

void main(){	

  TexCoords = aPos;
  //La matrice di vista utilizzata per trasformare i vertici 
  // non include la traslazione.
  // Questo significa che l'oggetto non si muoverà nello spazio 
  // della camera, ma la camera si muoverà attorno all'oggetto.
   //Matrice di vista a cui si toglie il contributo della traslazione
   
	mat4 Static_View = mat4(mat3(View));
	gl_Position = Projection*Static_View*vec4(aPos, 1.0);
    

}


