# RayTracingPlusPlus

*Implémentation d'un Raytracer en C++*

## But du projet

Le but de ce projet était de réaliser un raytracer simple, permettant de rendre des objets simple à l'aide de l'algorithme de lancer de rayon.

## Fonctionalités

- Rendu d'images et d'objets simples (sphères ou faces selon la syntaxe .obj)
- Calcul des ombres
- Calcul de divers coefficients pour rendre l'image photoréaliste : lumière ambiante, lumière diffuse, réflexion spéculaire
- Calcul de la réflexion et de la réfraction, à l'aide des formules de Snell-Descartes et de Fresnel
- Calcul et affichage du temps moyen restant avant génération de l'image
- Parallélisme (temps divisé par plus de 4)
- Support du format .obj
- Rendu vidéo possible en faisant varier une ou plusieurs des coordonnées d'un objet (interpolation linéaire)

## Comment utiliser ce raytracer

*Utiliser les fichiers d'input dans le répertoire input/. Diverses options s'offrent à vous*

1. Utiliser un fichier .obj (rien à faire, mais étant donné la grande variété des formats obj, ne fonctionne qu'avec un format obj en particulier : celui où on écrit `numéro du point / numéro texture / numéro normale)`

2. Utiliser un fichier d'input selon notre syntaxe spécifique

`sp (centre_x centre_y centre_z) rayon couleur_R couleur_V couleur_B refraction reflexion` pour déclarer une sphère

`li (centre_x centre_y centre_z) intensité couleur_R couleur_V couleur_B` pour déclarer une lumière

`ca (centre_x centre_y centre_z) (vec_dir_x vec_dir_y vec_dir_z) largeur hauteur angle (ory_x ory_y ory_z) (orx_x orx_y orx_z) couleur_R couleur_V couleur_B état` où état=true ou false, ce qui permet de mettre plusieurs caméra par scène.

Pour déclarer des sphères et des objets complexes en même temps, il suffit de mettre la syntaxe des sphères dans le fichier .obj lui-même.

Pour lancer le rendu, exécuter la commande suivante (le fichier doit être dans le répertoire `input/`) :

`./raytracer -video`

Pour lancer le mode video de démo

`./raytracer file_name refraction`

Avec file_name le nom du fichier à trouver (et le chemin) et refraction le coefficient de réfraction du mesh

L'image générée sera enregistrée sous la forme :

`output/sample.bmp`

## Exemples

Des exemples sont donnés dans le répertoire input/

## Licence du projet

*The MIT License (MIT)*

### Copyright (c) 2014 Epsichaos & Titif26

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
