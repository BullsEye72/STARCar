/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Class;

import IHM.TableauDeBord;
import de.javasoft.plaf.synthetica.*;
import java.net.MalformedURLException;
import java.text.ParseException;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;


/**
 *
 * @author Administrateur
 */
public class STARCar {

    /**
     * @param args the command line arguments
     */
    
    //private static ThreadRun thread = new ThreadRun();
           
    public static String tabCoordonnees[][];
    
    public static void main(String[] args) throws UnsupportedLookAndFeelException, ParseException, MalformedURLException, InterruptedException {
       
        UIManager.setLookAndFeel(new SyntheticaBlackEyeLookAndFeel());
        
        new TableauDeBord().setVisible(true);               
        
        //thread.run();        
    }
    
}
