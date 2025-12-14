# 🐿️ Robot-Écureuil Sauteur : Contrôle du Mécanisme d'Impulsion
Ce dépôt contient le code nécessaire à la mise en œuvre et au contrôle du mécanisme de chargement et de détente du robot-écureuil. Le système utilise un servomoteur pour armer le mécanisme et un capteur inertiel MPU6050 pour surveiller l'angle, assurant ainsi la précision du cycle de saut.

## ⚙️ Structure du DépôtLe dépôt est organisé autour de deux fichiers principaux :

1. `Arduino.ino` : Le code embarqué pour la carte Arduino, gérant le servomoteur, la lecture du MPU6050 (via I2C) et l'interprétation des commandes série.
2. `Control_clavier.py` : Un script Python qui permet de piloter le mécanisme via le clavier, en envoyant des commandes simples à la carte Arduino par communication série.

## 🛠️ Configuration Matérielle Pour répliquer ce système, vous aurez besoin de :

* **Robot écureuil :** Le robot écureuil, équipé d'une Arduino nano, d'un Servomoteur (attaché au Pin 9) pour le contrôle des pattes et d'un module MPU-6050 pour mesurer l'angle du robot
* **Interface :** Un PC avec Python et les librairies nécessaires pour le script de contrôle.

## 🕹️ Utilisation du Système
### 1. Code Arduino (`Arduino.ino`)
Ce programme utilise le MPU6050 pour lire l'angle Y du mécanisme avec un lissage sur six échantillons (`lastY1` à `lastY6`).

* **Initialisation :** Le servomoteur est mis à l'angle 90° (Stop).
* **Logique de Contrôle :**
  * Le moteur tourne à 180° (charge) tant que l'angle y est supérieur à 10° (condition d'arrêt du chargement).
  * La décharge se fait à 0° (mouvement inverse).


* **Commandes Série :**
  * `'c'` : Initialise la charge du mécanisme.
  * `'d'` : Tient le mécanisme en position de décharge (maintien du mouvement inverse).
  * `'s'` : Arrête le servomoteur (90°).



### 2. Script Python (`Control_Clavier.py`)
Ce script facilite le test du mécanisme en mappant les commandes série à des touches du clavier :

| Touche Clavier | Commande Envoyée | Action |
| --- | --- | --- |
| `up` ou `c` | `'c'` | Démarrer la charge (Armement). |
| `down` ou `d` | `'d'` | Décharge (Mouvement inverse maintenu). |
| *Aucune touche* | `'s'` | Arrêter le servomoteur. |

**Prérequis Python :**
Installez la librairie `pyserial` et `keyboard` :

```bash
pip install pyserial keyboard

```

**Exécution :**
Assurez-vous que le port série (`COM5` dans le code) corresponde bien au port de votre Arduino.

```bash
python Control_Clavier.py

```
