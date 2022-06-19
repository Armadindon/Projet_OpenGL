# 4I_IG1 - Projet OpenGL

![opengl_logo](image/opengl_logo.png)

Projet portant sur la réalisation, l'affichage et la navigation dans une scène 3D comportant plusieurs objets 3D.

# Développeurs

- Colin LE PICHON - colin.lepichon@edu.esiee.fr
- Mathieu PELLAN - mathieu.pellan@edu.esiee.fr
- Baptiste PERRIN - baptiste.perrin@edu.esiee.fr
- Mathieu TAILLANDIER - mathieu.taillandier@edu.esiee.fr

# Fonctionnement

Lors de la navigation dans la scène de test, vous pouvez déplacer la caméra à partir des touches : **Z, Q, S, D** et la faire pivoter à partir de **la souris**.

Vous retrouverez aussi une interface de paramétrage de la scène OpenGL. 
Pour pouvoir interagir avec cette dernière, il faut l'activer à partir de la touche **CTRL Gauche**.

## Interface de paramétrage

![ui](image/ui.png)

À partir d'une interface réajustable implémentée grâce à la librairie IMGUI, il est possible de changer divers paramètres :

- Les couleurs - les objets changent de couleur après qu'un code RGBA leur a été donné
- Les matériaux - les objets changent leurs matériels après la sélection d'un nouveau matériel (par défaut, le matériel chargé est celui associé au modèle.obj)
- La lumière - les différentes lumières de couleur émises
- La caméra - sa vitesse de déplacement et sa sensibilité à la souris
- Skybox - les différentes images de fond

# Réalisations

![ui](image/scene.png)

Lors de ce projet, nous avons réalisé divers développements basés sur un cahier des charges donné.

Nous avons alors implémenté :

- Plusieurs objets 3D sous format .obj avec des particularités différentes (textures ou matériaux) ; les objets ont été chargés grâce à la bibliothèque TinyOBJLoader
- Différents shaders sont présents pour les objets :
  - Shader pour cubemap
  - Shader de texture
  - Shader pour matériaux
  - Shader pour lumière
- Les objets 3D ont été imbriqués dans un format orienté objet de sorte à profiter de l'héritage et éviter de la redondance dans notre code
- Une illumination est présente au travers d'un objet émanant de la lumière
- La navigation se fait au travers de la gestion de la caméra à partir des touches précisées précédemment
- Une classe Matrix4 permettant de simplifier nos calculs
- Une interface graphique réalisée grâce à la bibliothèque IMGUI
- Un mappage d'environnement réalisé au travers de la réalisation d'une cubemap

# Conclusion

Ce projet a été très intéressant, il nous a permis de découvrir OpenGL ainsi que ses principales fonctionnalités. 

Nous les avons implémentées en parallèle de nos développements réalisés.
