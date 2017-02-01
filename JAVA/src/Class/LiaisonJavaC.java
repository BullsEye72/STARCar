/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Class;

import IHM.TableauDeBord;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Administrateur
 */
public class LiaisonJavaC {

    static SerialCommunicationCodeurQuantic commande = new SerialCommunicationCodeurQuantic();

    String messagePharesAvantON = "light 1 1\r"
            , messagePharesAvantOFF = "light 1 0\r"
            , messagePharesArriereON = "light 2 1\r"
            , messagePharesArriereOFF = "light 2 0\r"
            , messageEssuieGlaceON = "light 4 1\r"
            , messageEssuieGlaceOFF = "light 4 0\r"
            , messageClignotantGauche = "light 3 1\r"
            , messageClignotantDroit = "light 3 2\r"
            , messageWarningON = "light 3 3\r"
            , messageWarningOFF = "light 3 0\r"
            , messageToutDroit = "drive 1 "
            , messageRalentir = "drive 1 ";

    int[] vitesseTab = new int[6];

    public LiaisonJavaC() {

            vitesseTab[0] = 2000;
            vitesseTab[1] = 0;
            vitesseTab[2] = 2500;
            vitesseTab[3] = 5000;
            vitesseTab[4] = 7500;
            vitesseTab[5] = 10000;
        
        try {    
            commande.initSerialPort();
            commande.initwritetoport();
        } catch (Exception ex) {
            Logger.getLogger(LiaisonJavaC.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public void Acceler(int vitesse) {

        int vitesseMoteur = 0;
        int direction = 0;

        switch (vitesse) {

            case 0:
                vitesseMoteur = vitesseTab[1];
                direction = 0;
                break;

            case 1:
                vitesseMoteur = vitesseTab[2];
                direction = 1;
                break;

            case 2:
                vitesseMoteur = vitesseTab[3];
                direction = 1;
                break;

            case 3:
                vitesseMoteur = vitesseTab[4];
                direction = 1;
                break;

            case 4:
                vitesseMoteur = vitesseTab[5];
                direction = 1;
                break;
        }

        /*TableauDeBord.barRPM.setValue(vitesseMoteur);
        TableauDeBord.fieldRPM.setText(vitesseMoteur + " RPM");*/
        commande.writetoport(messageToutDroit + vitesseMoteur + "\r");
    }

    public void Freiner(int vitesse) {

        int vitesseMoteur = 0;
        int direction = 0;

        switch (vitesse) {

            case -1:
                vitesseMoteur = vitesseTab[0];
                direction = 2;
                break;

            case 0:
                vitesseMoteur = vitesseTab[1];
                direction = 0;
                break;

            case 1:
                vitesseMoteur = vitesseTab[2];
                direction = 1;
                break;

            case 2:
                vitesseMoteur = vitesseTab[3];
                direction = 1;
                break;

            case 3:
                vitesseMoteur = vitesseTab[4];
                direction = 1;
                break;
        }

        /*TableauDeBord.barRPM.setValue(vitesseMoteur);
        TableauDeBord.fieldRPM.setText(vitesseMoteur + " RPM");*/
        commande.writetoport(messageRalentir + vitesseMoteur + "\r");
    }

    public void Droite() {
        commande.writetoport(messageClignotantDroit);
        commande.writetoport("turn 2\r");
    }

    public void ToutDroit() {
        commande.writetoport(messageWarningOFF);
        commande.writetoport("turn 0\r");
    }

    public void Gauche() {
        commande.writetoport(messageClignotantGauche);
        commande.writetoport("turn 1\r");
    }

    public void EssuieGlace(boolean etat) {
        if (etat == true) {
            commande.writetoport(messageEssuieGlaceOFF);
        } else {
            commande.writetoport(messageEssuieGlaceON);
        }
    }

    public void Warning(boolean etat) {
        if (etat == true) {
            commande.writetoport(messageWarningOFF);
        } else {
            commande.writetoport(messageWarningON);
        }
    }

    public void PhareAvant(boolean etat) {
        if (etat == true) {
            commande.writetoport(messagePharesAvantOFF);
        } else {
            commande.writetoport(messagePharesAvantON);
        }
    }

    public void PhareArriere(boolean etat) {
        if (etat == true) {
            commande.writetoport(messagePharesArriereOFF);
        } else {
            commande.writetoport(messagePharesArriereON);
        }
    }

    public static void majCompteTour(int vitesseMoteur) {
        
        TableauDeBord.barRPM.setValue(vitesseMoteur);
        TableauDeBord.barRPM.updateUI();
        
        TableauDeBord.fieldRPM.setText(vitesseMoteur + " RPM");
    }

    public void ClignotantGauche(boolean etat) {
        if (etat == true) {
            commande.writetoport(messageWarningOFF);
        } else {
            commande.writetoport(messageClignotantGauche);
        }
    }

    public void ClignotantDroit(boolean etat) {
        if (etat == true)
        {
            commande.writetoport(messageWarningOFF);
        } else
        {
            commande.writetoport(messageClignotantDroit);
        }
    }
}
