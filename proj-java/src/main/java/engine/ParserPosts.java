package engine;

import java.io.File;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import java.time.LocalDate;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import common.Comunidade;

/**
 * Write a description of class ParserPosts here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ParserPosts
{
   /**
    * Parser dos Posts (Questions e Answers)
    * 
    * @param    c   Comunidade
    * @param    FileP   Path para o ficheiro xml onde se encontra a informaçao necessaria
    * 
    * @return    (Comunidade)   A Comunidade alterada
    */
    public static Comunidade functionP(Comunidade c, String FileP){
      try {
         File inputFile = new File(FileP);
         SAXParserFactory ppf = SAXParserFactory.newInstance();
         SAXParser pp = ppf.newSAXParser();
         PP parse = new PP(c);
         pp.parse(inputFile,parse);       
      } catch (Exception e) {
         e.printStackTrace();
      }
      return c;
   }
}

class PP extends DefaultHandler{
    private Comunidade c;
    
    public PP(Comunidade c){
        super();
        this.c = c;
    }
    
    @Override
    public void startElement (String newS, String newS2, String nomeUsado, Attributes a)throws SAXException{
        if(nomeUsado.equalsIgnoreCase("row")){
            long ptid = 0;
            if (a.getIndex("PostTypeId")!=-1) ptid = Integer.parseInt(a.getValue("PostTypeId"));
               if(a.getValue("PostTypeId").equals("1")){
                   
                   //________________________________________________________________________
                   
                   long id = 0;
                   if(a.getIndex("Id") != -1){
                        id=Long.parseLong(a.getValue("Id"));
                   }
                   LocalDate data = LocalDate.of(1,1,1);
                   if(a.getIndex("CreationDate") != -1){
                       data = c.convert(a.getValue("CreationDate"));
                   }
                   long owid = 0;
                   if(a.getIndex("OwnerUserId") != -1){
                       owid = Long.parseLong(a.getValue("OwnerUserId"));
                   }
                   List<String> tags = new ArrayList<>();
                   if(a.getIndex("Tags") != -1){
                       tags = c.toAL(a.getValue("Tags"));
                   }
                   String title = "";
                   if(a.getIndex("Title") != -1){
                       title = a.getValue("Title");
                   }
                   int anscount = 0;
                   if(a.getIndex("AnswerCount") != -1){
                       anscount = Integer.parseInt(a.getValue("AnswerCount"));
                   }
                   
                   
                   if((id != 0) && (owid != 0) ){
                   c.addQuestion(id,data,owid,tags,title,anscount);
                   c.addQuestionToUser(id,data,owid,tags,title,anscount);
                  }
               }
               if(a.getValue("PostTypeId").equals("2")){
                   
                   
                   
                   //________________________________________________________________________
                   
                   long id = 0;
                   if(a.getIndex("Id") != -1){
                        id=Long.parseLong(a.getValue("Id"));
                   }
                   LocalDate data = LocalDate.of(1,1,1);
                   if(a.getIndex("CreationDate") != -1){
                       data = c.convert(a.getValue("CreationDate"));
                   }
                   long owid = 0;
                   if(a.getIndex("OwnerUserId") != -1){
                       owid = Long.parseLong(a.getValue("OwnerUserId"));
                   }
                   long pid = 0;
                   if(a.getIndex("ParentId") != -1){
                       pid = Long.parseLong(a.getValue("ParentId"));
                   }
                   int score = 0;
                   if(a.getIndex("Score") != -1){
                       score = Integer.parseInt(a.getValue("Score"));
                   }
                   int comcount = 0;
                   if(a.getIndex("CommentCount") != -1){
                       comcount = Integer.parseInt(a.getValue("CommentCount"));
                   }
                   
                   if((id != 0) && (owid != 0) ){
                   c.addAnswer(id,data,owid,pid,score,comcount);
                   c.addAnswerToUser(id,data,owid,pid,score,comcount);
                   c.addAnswerToQuestion(id,data,owid,pid,score,comcount);
                  }
               }
        }
    }
}