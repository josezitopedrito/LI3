package engine;

import java.io.File;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import common.Comunidade;
/**
 * Write a description of class ParserPosts here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ParserTags{
   /**
    * Parser das Tags
    * 
    * @param    c   Comunidade
    * @param    FileT   Path para o ficheiro xml onde se encontra a informaçao necessaria
    * 
    * @return    (Comunidade)   A Comunidade alterada
    */
   
   public static Comunidade functionT(Comunidade c, String FileT) {
      try {
         File inputFile = new File(FileT);
         SAXParserFactory ptf = SAXParserFactory.newInstance();
         SAXParser pt = ptf.newSAXParser();
         PT parse = new PT(c);
         pt.parse(inputFile,parse);         
      } catch (Exception e) {
         e.printStackTrace();
      }
      return c;
   }
}

class PT extends DefaultHandler{
    private Comunidade c;
    public PT(Comunidade c){
        super();
        this.c = c;
    }
    
    @Override
    public void startElement (String newS, String newS2, String nomeUsado, Attributes a)throws SAXException{
         if(nomeUsado.equalsIgnoreCase("row")){
            long id = 0;
            String tagName = "";
            if(a.getIndex("TagName") != -1) tagName = a.getValue("TagName");
            if(a.getIndex("Id") != -1) id = Long.parseLong(a.getValue("Id"));
            if ((id != 0) && (!tagName.equals(""))) {
                c.addTag(id,tagName);                
            }
        }
    }
}
