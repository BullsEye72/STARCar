/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Class;

import IHM.TableauDeBord;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 *
 * @author BAPTISTE
 */
public class Direction {

    public static String tabCoordonnees[][];
    public static int Vitesse;
    private float resX;
    private float resY;
    private float PostPREC = 0;
    
    private static LiaisonJavaC voiture;
    
    public String CalculDirection(float DepartX, float DepartY, float ArriveX, float ArriveY) {
        resX = ArriveX - DepartX;
        resY = ArriveY - DepartY;
        resX = (float) Math.atan(resY / resX);
        resX = (float) Math.toDegrees(resX);
        if (PostPREC == 0) {
            PostPREC = resX;
        }
        return getDirection(PostPREC, resX);
    }

    public void SetDirectionToURL(String lat, String Long, String Speed) throws MalformedURLException, IOException, InterruptedException {
        String URLchaine;
        URLchaine = "http://bullseye.freeboxos.fr:5055/?id=000003&lat=" + lat + "&lon=" + Long + "&speed=" + Speed + "";

        URL monURL = new URL(URLchaine);
        Thread.sleep(Vitesse / Integer.parseInt(Speed));
        URLConnection connexion = monURL.openConnection();
        InputStream flux = connexion.getInputStream();
        flux.close();
    }

    public String getDirection(Float degresP, Float degresA) {
        int DTolerance = 15;
        String Madirection;

        if ((degresA > (degresP - DTolerance)) && (degresA < (degresP + DTolerance))) {
            Madirection = "forward";
        } else if ((degresP < degresA) && (degresA < (degresP + 180))) {
            Madirection = "right";
        } else {
            Madirection = "left";
        }

        PostPREC = degresA;

        return Madirection;
    }

    public void DirectionINI(String NomXML, boolean MarcheAvantArriere, int vitesseParam) throws MalformedURLException, InterruptedException {
        
        voiture = TableauDeBord.getLiaison();
        
        final DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try {
            int test = 0;
            Vitesse = vitesseParam;
            final DocumentBuilder builder = factory.newDocumentBuilder();
            final Document document = builder.parse(new File(NomXML));
            //Direction Madirection= new Direction();
            //Affiche la version de XML
            //System.out.println(document.getXmlVersion());

            //Affiche l'encodage
            //System.out.println(document.getXmlEncoding());	
            //Affiche s'il s'agit d'un document standalone		
            //System.out.println(document.getXmlStandalone());
            final Element racine = document.getDocumentElement();
            //System.out.println(racine.getNodeName());

            final NodeList racineNoeuds = racine.getChildNodes();

            final int nbRacineNoeuds = racineNoeuds.getLength();

            if (nbRacineNoeuds != 0) {
                tabCoordonnees = new String[nbRacineNoeuds][3];
            }
            for (int i = 0; i < nbRacineNoeuds; i++) {
                if (racineNoeuds.item(i).getNodeType() == Node.ELEMENT_NODE) {
                    final Element coordon = (Element) racineNoeuds.item(i);
                    tabCoordonnees[test][0] = coordon.getAttribute("gear");
                    tabCoordonnees[test][1] = coordon.getAttribute("latitude");
                    tabCoordonnees[test][2] = coordon.getAttribute("longitude");

                    test++;
                    //System.out.println("gear : " + coordon.getAttribute("gear")+"  lat : " + coordon.getAttribute("latitude")+"  long : " + coordon.getAttribute("longitude"));
                    //System.out.println(tabCoordonnees[i][0]+" "+tabCoordonnees[i][1]+" "+ tabCoordonnees[i][2]);

                }

            }
            //while(true){
            tabCoordonnees[test][0] = tabCoordonnees[0][0];
            tabCoordonnees[test][1] = tabCoordonnees[0][1];
            tabCoordonnees[test][2] = tabCoordonnees[0][2];

            if (MarcheAvantArriere == true) {
                for (int y = 0; y < (test); y++) {
                    if (tabCoordonnees[y][0] != null) {
                        SetDirectionToURL(tabCoordonnees[y][1], tabCoordonnees[y][2], tabCoordonnees[y][0]);
                        EnvoiCarteEmbarque(CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y + 1][1]), Float.parseFloat(tabCoordonnees[y + 1][2])));
                        // DirectionPrec=Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y+1][1]), Float.parseFloat(tabCoordonnees[y+1][2]));
                    }
                }
            } else {
                for (int y = (test); y > 0; y--) {
                    if (tabCoordonnees[y][0] != null) {
                        SetDirectionToURL(tabCoordonnees[y][1], tabCoordonnees[y][2], tabCoordonnees[y][0]);
                        EnvoiCarteEmbarque(CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y - 1][1]), Float.parseFloat(tabCoordonnees[y - 1][2])));
                        // DirectionPrec=Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y+1][1]), Float.parseFloat(tabCoordonnees[y+1][2]));
                    }
                }
            }

            //}
        } catch (final ParserConfigurationException e) {
            e.printStackTrace();
        } catch (final SAXException e) {
            e.printStackTrace();
        } catch (final IOException e) {
            e.printStackTrace();
        }
    }

    public void EnvoiCarteEmbarque(String MaDirection) {
        switch (MaDirection) {
            case "forward":
                // Statements
                TableauDeBord.barRPM.setValue(10000);
                TableauDeBord.fieldRPM.setText("10000 RPM");
                voiture.Acceler(4);
                
                voiture.ToutDroit();
                break; // optional

            case "right":
                // Statements
                TableauDeBord.barRPM.setValue(5000);
                TableauDeBord.fieldRPM.setText("5000 RPM");
                voiture.Freiner(2);
                voiture.Droite();
                break; // optional

            case "left":
                // Statements
                TableauDeBord.barRPM.setValue(5000);
                TableauDeBord.fieldRPM.setText("5000 RPM");
                voiture.Freiner(2);
                voiture.Gauche();
                break; // optional   
            // You can have any number of case statements.
            default: // Optional
            // Statements
        }
    }
}
