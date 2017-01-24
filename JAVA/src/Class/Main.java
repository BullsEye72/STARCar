/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Class;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import org.w3c.dom.Document;
import java.io.IOException;
import java.net.MalformedURLException;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
/**
 *
 * @author BAPTISTE
 */
public class Main {
    public static String tabCoordonnees[][];
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws MalformedURLException, InterruptedException {
        // TODO code application logic here
        final DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try {
            int test=0;
            boolean sens=true;
            String DirectionPrec;
            final DocumentBuilder builder = factory.newDocumentBuilder();		
            final Document document= builder.parse(new File("Circuit CCI.xml"));
            Direction Madirection= new Direction();
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
		
            if (nbRacineNoeuds != 0){
                tabCoordonnees = new String [nbRacineNoeuds][3];
            }
            for (int i = 0; i<nbRacineNoeuds; i++) {
                if(racineNoeuds.item(i).getNodeType() == Node.ELEMENT_NODE) {
                 final Element coordon = (Element) racineNoeuds.item(i);
                 tabCoordonnees[test][0]=coordon.getAttribute("gear");
                 tabCoordonnees[test][1]=coordon.getAttribute("latitude");
                 tabCoordonnees[test][2]=coordon.getAttribute("longitude");
                 
                 test++;
                 //System.out.println("gear : " + coordon.getAttribute("gear")+"  lat : " + coordon.getAttribute("latitude")+"  long : " + coordon.getAttribute("longitude"));
                //System.out.println(tabCoordonnees[i][0]+" "+tabCoordonnees[i][1]+" "+ tabCoordonnees[i][2]);
                
                }
               
            }
            //while(true){
                 tabCoordonnees[test][0]=tabCoordonnees[0][0];
                 tabCoordonnees[test][1]=tabCoordonnees[0][1];
                 tabCoordonnees[test][2]=tabCoordonnees[0][2];
                 
            if (sens==true){
                for (int y = 0; y<(test); y++) {
                    if(tabCoordonnees[y][0]!=null){
                        Madirection.SetDirectionToURL(tabCoordonnees[y][1], tabCoordonnees[y][2], tabCoordonnees[y][0]);
                        System.out.println(Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y+1][1]), Float.parseFloat(tabCoordonnees[y+1][2])));
                       // DirectionPrec=Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y+1][1]), Float.parseFloat(tabCoordonnees[y+1][2]));
                    }
                }
            }else{
                for (int y = (test); y>0; y--) {
                    if(tabCoordonnees[y][0]!=null){
                        Madirection.SetDirectionToURL(tabCoordonnees[y][1], tabCoordonnees[y][2], tabCoordonnees[y][0]);
                        System.out.println(Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y-1][1]), Float.parseFloat(tabCoordonnees[y-1][2])));
                       // DirectionPrec=Madirection.CalculDirection(Float.parseFloat(tabCoordonnees[y][1]), Float.parseFloat(tabCoordonnees[y][2]), Float.parseFloat(tabCoordonnees[y+1][1]), Float.parseFloat(tabCoordonnees[y+1][2]));
                    }
                }
            }


            //}

        }
        catch (final ParserConfigurationException e) {
            e.printStackTrace();
        }
        catch (final SAXException e) {
            e.printStackTrace();
        }
        catch (final IOException e) {
            e.printStackTrace();
        }
    }
    
}
