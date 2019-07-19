package common;

import java.util.List;
import java.util.ArrayList;
import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
/**
 * Write a description of class Questions here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Questions extends Posts
{
    /**
     * Lista com as tags da Question
     */
    private List<String> tags;
    /**
     * Numero de tags que a Question tem
     */
    private int numtag;
    /**
     * String com o titulo da Question
     */
    private String title;
    /**
     * Numero de Answers que a Question tem
     */
    private int anscount;
    /**
     * Map com as Answers como Value e com a data de criaçao destas como key
     */
    private List<Answers> ans;

    /**
     * Construtor vazio da classe Questions
     */
    public Questions()
    {
        super();
        this.tags = new ArrayList<>();
        this.numtag = 0;
        this.title = "Titulo predefinido";
        this.anscount = 0;
        this.ans = new ArrayList<>();
    }
    //----------------------------------------------------------------------
    /**
     * Construtor parameterizado da classe Questions
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   tags    Lista com as tags da Question
     * @param   title    Titulo da Question
     * @param   anscount    Numero de Answers que respondem a Question
     * @param   Map<LocalDate,Answers>   Map com as Answers como Value e com a data de criaçao destas como key
     */
    public Questions(long id, LocalDate data, long owneruserid, List<String> tags, int numtag, String title, int anscount, List<Answers> ans){
        super(id,data,owneruserid);
        this.setTags(tags);
        this.numtag = numtag;
        this.title = title;
        this.anscount = anscount;
        this.setAns(ans);
    }
    //----------------------------------------------------------------------
    /**
     * Construtor copia da classe Questions
     */
    public Questions(Questions q){
        super(q);
        this.tags = q.getTags();
        this.numtag = q.getNumtags();
        this.title = q.getTitle();
        this.anscount = q.getAnscount();
        this.ans = q.getAns();
    }
    //----------------------------------------------------------------------
    /**
     * Get da Tags da Question
     * 
     * @return   (List<String>)    Lista com as Tags da Question
     */
    public List<String> getTags(){
        List<String> res = new ArrayList<> ();
        for(String s : tags){
            res.add(s);
        }
        return res;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Numero de Tags da Question
     * 
     * @return   (int)    Numero de Tags da Question
     */
    public int getNumtags(){
        return this.numtag;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Titulo da Question
     * 
     * @return   (String)    Titulo da Question
     */
    public String getTitle(){
        return this.title;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Numero de Answers da Question
     * 
     * @return   (int)    Numero de Answers da Question
     */
    public int getAnscount(){
        return this.anscount;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Mapa de Answers da Question
     * 
     * @return   (Map<LocalDate,Answers>)    Mapa com as Answers da Question
     */
    public List<Answers> getAns(){
        List<Answers> res = new ArrayList<> ();
        for(Answers a : ans){
            res.add(a);
        }
        return res;
    }
    //----------------------------------------------------------------------
    /**
     * Set da Tags da Question
     * 
     * @param    Lista com as Tags da Question
     */
    public void setTags(List<String> f){
        this.tags= new ArrayList<>(f.size());
        f.forEach (s -> this.tags.add(s));
    }
    //----------------------------------------------------------------------
    /**
     * Set do Numero de Tags da Question
     * 
     * @param    Numero de Tags da Question
     */
    public void setNumtags (int numtag){
        this.numtag = numtag;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Titulo da Question
     * 
     * @param    Titulo da Question
     */
    public void setTitle (String title){
        this.title = title;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Numero de Answers da Question
     * 
     * @param    Lista com as Tags da Question
     */
    public void setAnscount (int anscount){
        this.anscount = anscount;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Mapa de Answers da Question
     * 
     * @param    Mapa com as Answers da Question
     */
    public void setAns(List<Answers> ans){
        this.ans = new ArrayList<>(ans.size());
        ans.forEach (a -> this.ans.add(a.clone()));
    }
    //________________________________________________________________________
    /**
     * Metodo clone da classe Questions
     * 
     * return   (Questions)    Clone da classe Questions
     */
    public Questions clone(){
        return new Questions(this);
    }
    
    /**
     * Metodo toString da classe Questions
     * 
     * @return   (String)   String com a informaçao da classe Questions
     */
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("Questions{ Tags");
        sb.append(this.getTags());
        sb.append(", Numero de Tags:");
        sb.append(this.getNumtags());
        sb.append(", Titulo da questions:");
        sb.append(this.getTitle());
        sb.append(", Numero de answers:");
        sb.append(this.getAnscount());
        sb.append(", Answers desta question:");
        sb.append(this.getAns());
        sb.append("}");
        return sb.toString();
    }
    
    /**
     *  Metodo equals da classe Questions
     *  
     *  @param o    Objeto a ser comparado
     *  @return (boolean)   true se forem iguais false se nao o forem
     */
    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Questions q = (Questions) o;
        return tags.equals(q.getTags()) && q.getNumtags() == numtag && title.equals(q.getTitle()) && q.getAnscount() == anscount && ans.equals(getAns());
    }
}
