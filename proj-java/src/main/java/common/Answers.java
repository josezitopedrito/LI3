package common;

import java.time.LocalDate;
/**
 * Write a description of class Answers here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Answers extends Posts
{
    /**
     * Id da Question a qual esta Answer responde
     */
    private long parentid;
    /**
     * Score da Answer
     */
    private int score;
    /**
     * Numero de comentarios da Answer
     */
    private int comcount;

    /**
     * Construtor vazio da classe Answers
     */
    public Answers(){
        this.parentid = 0;
        this.score = 0;
        this.comcount = 0;
    }
    //----------------------------------------------------------------------
    /**
     * Construtor parameterizado da classe Answers
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   parentid    Id da Question a que esta Answer responde
     * @param   score    Score da Answer
     * @param   comcount    Numero de Comments da Answer
     */
    public Answers(long id, LocalDate data, long owneruserid, long parentid, int score, int comcount){
        super(id,data,owneruserid);
        this.parentid = parentid;
        this.score = score;
        this.comcount = comcount;
    }
    //----------------------------------------------------------------------
    /**
     * Construtor copia da classe Answers
     */
    public Answers(Answers a){
        super(a);
        this.parentid = a.getParentid();
        this.score = a.getScore();
        this.comcount = a.getComcount();
    }
    //----------------------------------------------------------------------
    /**
     * Get do ParentId da Answer
     * 
     * @return   (Long)    ParentId da Answer
     */
    public long getParentid(){
        return this.parentid;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Score da Answer
     * 
     * @return   (int)    Score da Answer
     */
    public int getScore(){
        return this.score;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Numero de Comments da Answer
     * 
     * @return   (int)    Numero de Comments da Answer
     */
    public int getComcount(){
        return this.comcount;
    }
    //----------------------------------------------------------------------
    /**
     * Set do ParentId da Answer
     * 
     * @param    Novo ParentId da Answer
     */
    public void setParentid(long parentid){
        this.parentid = parentid;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Score da Answer
     * 
     * @param    Novo Score da Answer
     */
    public void setScore(int score){
        this.score = score;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Numero de Comments da Answer
     * 
     * @param    Numero de Comments da Answer
     */
    public void setComcount(int comcount){
        this.comcount = comcount;
    }
    //----------------------------------------------------------------------
    /**
     * Metodo Clone da classe Answers
     * 
     * @return  (Answers)   Copia da classe Answers
     */
    public Answers clone(){
        return new Answers(this);
    }
    
    /**
     * Metodo toString da classe Answers
     * 
     * @return  (String)    String que contem a informaçao da classe Answers
     */
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("Answers{O id da question a qual a answer responde:");
        sb.append(this.getParentid());
        sb.append(", o Score da answer:");
        sb.append(this.getScore());
        sb.append(", o numero de comentarios da answer:");
        sb.append(this.getComcount());
        sb.append("}");
        return sb.toString();
    }
    
    /**
     *  Metodo equals da classe Answers
     *  
     *  @param o    Objeto a ser comparado
     *  @return (boolean)   true se forem iguais false se nao o forem
     */
    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Answers a = (Answers) o;
        return a.getParentid() == parentid && a.getScore() == score && a.getComcount() == comcount;
    }
}
