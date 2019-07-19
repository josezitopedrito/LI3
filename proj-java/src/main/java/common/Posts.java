package common;

import java.time.LocalDate;

/**
 * Abstract class Posts - write a description of the class here
 *
 * @author (your name here)
 * @version (version number or date here)
 */
public abstract class Posts
{
    /**
     * Id do post
     */
    private long id;
    /**
     * Data de criaçao do post
     */
    private LocalDate data;
    /**
     * Id do criador do post
     */
    private long owneruserid;
    
    /**
     * Construtor vazio da classe Posts
     */
    public Posts(){
        this.id = 0;
        this.data = LocalDate.of(1,1,1);
        this.owneruserid = 0;
    }
    //----------------------------------------------------------------------
    /**
     * Construtor parameterizado da classe Posts
     * 
     * @param   id    Id do Post
     * @param   data    Data de criaçao do Post
     * @param   owneruserid    Id do criador do Post
     */
    public Posts(long id, LocalDate data, long owneruserid){
        this.id = id;
        this.data = data;
        this.owneruserid = owneruserid;
    }
    //----------------------------------------------------------------------
    /**
     * Construtor parameterizado da classe Posts
     */
    public Posts(Posts p){
        this.id = p.getId();
        this.data = p.getData();
        this.owneruserid = p.getOwneruserid();
    }
    //----------------------------------------------------------------------
    /**
     * Get do Id do Post
     * 
     * @return   (Long)    Id do Post
     */
    public long getId(){
        return this.id;
    }
    //----------------------------------------------------------------------
    /**
     * Get do Id do criador do Post
     * 
     * @return   (Long)    Id do criador do Post
     */
    public long getOwneruserid(){
        return this.owneruserid;
    }
    //----------------------------------------------------------------------
    /**
     * Get da Data de criaçao do Post
     * 
     * @return   (LocalDate)    Data de criaçao do Post
     */
    public LocalDate getData(){
        return this.data;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Id do Post
     * 
     * @param    Novo Id do Post
     */
    public void setId(long id){
        this.id = id;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Id do criador do Post
     * 
     * @param    Id do criador do Post
     */
    public void setOwneruserid(long owneruserid){
        this.owneruserid = owneruserid;
    }
    //----------------------------------------------------------------------
    /**
     * Set do Id do Post
     * 
     * @param    Data de criaçao do Post
     */
    public void setData(LocalDate data){
        this.data = data;
    }
    //----------------------------------------------------------------------
    /**
     * Metodo Clone da classe abtrata Posts
     */
    public abstract Posts clone();
    
    /**
     * Metodo toString da classe Posts
     * 
     * @return  (String)    String que contem a informaçao da classe Posts
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Posts{O id do post:");
        sb.append(this.getId());
        sb.append(", o Id do criador do Post:");
        sb.append(this.getOwneruserid());
        sb.append(", a data de criaçao do Post:");
        sb.append(this.getData());
        sb.append("}");
        return sb.toString();
    }
    
    /**
     *  Metodo equals da classe Posts
     *  
     *  @param o    Objeto a ser comparado
     *  @return (boolean)   true se forem iguais false se nao o forem
     */
     public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Posts p = (Posts) o;
        return p.getId() == id && p.getOwneruserid() == owneruserid && data.equals(p.getData());
    }
}
