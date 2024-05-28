# GLaDOS - Robotique

La partie robotique du projet GLaDOS est faite avec arduino.

Le robot en lui-même est partiellement imprimé en 3D, excepté pour les composants qui lui permettent de bouger.<br>
Nous nous sommes basé sur une version modifié du EEZYBot mk2 pouvant accueilir des stepper motor.

**TODO :**
- [ ] switch de butée stepper (ou autre solution permettant de connaître la position du bras)
- [ ] Régler / Tester les limites des moteurs (Stutter au dessus d'une speed de 1000 et accel de 500 -> A voir avec l'alim)
- [ ] Vis bloquantes
- [ ] Documentation modélisation 3D
- [ ] Troubleshoot moteur bruyant et qui saccadent.

## Ressources utiles

[Tuto utilisation board CNC](https://www.aranacorp.com/en/using-an-arduino-cnc-shield-v3/)<br>
[Tuto configuration des drivers](https://www.youtube.com/watch?v=OpaUwWouyE0)  

## Arduino

Le fichier à importer se trouve dans le répertoire **./src/** .

Il permet à l'heure actuelle de tester l'amplitude du bras. Il ne faut pas oublier de home le bras avant chaque démarrage, une fonction de homin est développé mais les limit switch ne sont pas en place.

Configuration actuelle :
- 80 steps pour le moteur gérant la profondeur.
- 60 steps pour le moteur gérant la hauteur.

On utilise la librairie arduino "AccelStepper.h" afin de contrôler comme son nom l'indique l'acceleration des stepper (essayer de s'approcher d'un mouvement organique).


## Composants

### Cnc shield V3

Pour contrôler les stepper motor on utilise un shield cnc arduino avec des drivers A4988.<br>
Les drivers s'insèrent *(dans le sens du texte sur le shield)* vis vers le bas.

> Une image du shield : <br>
<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.diyelectronics.co.za%2Fstore%2F6052-thickbox_default%2Farduino-cnc-shield-v3-kit.jpg&f=1&nofb=1&ipt=e73f31d78033063469e8bbc55788807fffd799c522c214a858528bb14d7634d6&ipo=images" alt="shield" style="width: 300px">

**Configuration:**

Le shield est alimenté séparément en 12V.

On insère la fiche des steppers dans les pins situés à coté des drivers avec la partie en metal exposé du côté droit. De cette manière on évite de se tromper sur le sens de rotation des stepper.

**Ref:** Fditdhu9inq27v *(Compatible drivers A4988 / DRV8825)*

### Driver `A4988`

> Une image du driver A4988:<br>
<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Frobosynckits.in%2Fwp-content%2Fuploads%2F2020%2F12%2FA48899.jpg&f=1&nofb=1&ipt=b3313075896395417277e692a60fd157420deff714ada455da7d07f5c0a75085&ipo=images" alt="driver" style="width: 300px">

**Configuration:**

Vref = 8 * 1.5 * 0.068
       Facteur dans la doc * Courant phase maximum * Résistance du drivers (board)

Il faut tourner la vis du drivers pour régler à la valeur de Vref.

### Stepper motor `KL17H248-15-4A`

> Une image du moteur KL17H248-15-4A:<br>
<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fm.media-amazon.com%2Fimages%2FI%2F41WpOa0REKL._SY445_SX342_QL70_ML2_.jpg&f=1&nofb=1&ipt=fb1c8fe50917dd02a9cf61bd972f1871a6c354bc11754106059133cf7782e4ee&ipo=images" alt="driver" style="width: 300px">

Les step motors que l'on utilise sont ceux qui se trouvaient anciennement dans la ROSTOCK MAX v2.

Le moteur fait un révolution complète en 200 steps.<br>
Les deux moteurs qui gère le déplacement de la tête on comme sens positif le sens horaire (CW).<br>
Les angles limites associés au modèle 3D de GLaDOS por ces moteur sont:
- Profondeur : 180° (100 steps)
- Hauteur : 135° (75 steps)


