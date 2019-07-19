package engine;

import java.io.File;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import common.Comunidade;

/**
 * Write a description of class Parser here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ParserUsers {        
   /**
    * Parser dos Users
    * 
    * @param    c   Comunidade
    * @param    FileU   Path para o ficheiro xml onde se encontra a informaçao necessaria
    * 
    * @return    (Comunidade)   A Comunidade alterada
    */
   public static Comunidade functionU(Comunidade c, String FileU) {
      try {
         File inputFile = new File(FileU);
         SAXParserFactory puf = SAXParserFactory.newInstance();
         SAXParser pu = puf.newSAXParser();
         PU parse = new PU(c);
         pu.parse(inputFile,parse); 
      } catch (Exception e) {
         e.printStackTrace();
      }
      return c;
   }
}

class PU extends DefaultHandler{
    private Comunidade c;
    
    
    public PU(Comunidade c){
        super();
        this.c = c;
    }
    
    @Override
    public void startElement (String newS, String newS2, String nomeUsado, Attributes a)throws SAXException{
        if(nomeUsado.equalsIgnoreCase("row")){
            long id = 0;
            long rep = 0;
            String dispN = "";
            String aM = "";
            if(a.getIndex("Id") != -1) id = Long.parseLong(a.getValue("Id"));
            if(a.getIndex("Reputation") != -1) rep = Long.parseLong(a.getValue("Reputation"));
            if(a.getIndex("DisplayName") != -1) dispN = a.getValue("DisplayName");
            if(a.getIndex("AboutMe") != -1) aM = a.getValue("AboutMe");
            if ((id != 0) && (rep != 0) && (!dispN.equals(""))){
               c.addUser(dispN,aM,rep,id);
            }
        }
    }
}
