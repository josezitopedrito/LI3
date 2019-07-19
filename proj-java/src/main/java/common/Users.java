package common;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.time.LocalDate;

/**
 * Write a description of class Users here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Users
{
    /**
     * Nome do User
     */
    private String name;
    /**
     * AboutMe do User
     */
    private String aboutme;
    /**
     * Reputaçao do User
     */
    private long rep;
    /**
     * Id do User
     */
    private long id;
    /**
     * Numero de Questoes do User
     */
    private int numques;
    /**
     * Numero de Answers do User
     */
    private int numans;
    /**
     * TreeMap com Questions como values e as suas datas de criaçao como keys
     */
    private List<Questions> ques;
    /**
     * TreeMap com Answers como values e as suas datas de criaçao como keys
     */
    private List<Answers> ans;
    /**
     * Construtor vazio da classe Users
     */
    public Users(){
        this.name = "Nome";
        this.aboutme = "Historia";
        this.rep = 0;
        this.id = 0;
        this.numques = 0;
        this.numans = 0;
        this.ques = new ArrayList<>();
        this.ans = new ArrayList<>();
    }
    
    /**
     * Construtor parameterizado da classe Users
     * 
     * @param   name    Nome do User
     * @param   aboutme    AboutMe do User
     * @param   rep    Reputaçao do User
     * @param   id    Id do User
     * @param   numques    Numero de Questoes do User
     * @param   numans    Numero de Answers do User
     * @param   ques    TreeMap com Questions como values e as suas datas de criaçao como keys
     * @param   ans    TreeMap com Answers como values e as suas datas de criaçao como keys
     */
    public Users(String name, String aboutme, long rep, long id, int numques, int numans, ArrayList<Questions> ques, ArrayList<Answers> ans){
        this.name = name;
        this.aboutme = aboutme;
        this.rep = rep;
        this.id = id;
        this.numques = numques;
        this.numans = numans;
        this.setQues(ques);
        this.setAns(ans);
    }
    
    /**
     * Construtor copia da classe Users
     */
    public Users(Users u){
        this.name = u.getName();
        this.aboutme = u.getAboutMe();
        this.rep = u.getRep();
        this.id = u.getId();
        this.numques = u.getNumQues();
        this.numans = u.getNumAns();
        this.ques = u.getQues();
        this.ans = u.getAns();
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o Nome do User fornecido como parâmetro
     * 
     * @return   (String)   O Nome do User 
     */
    public String getName(){
        return this.name;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o AboutMe do User fornecido como parâmetro
     * 
     * @return   (String)   O AboutMe do User 
     */
    public String getAboutMe(){
        return this.aboutme;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o Id do User fornecido como parâmetro
     * 
     * @return   (long)   O Id do User 
     */
    public long getId(){
        return this.id;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece a reputação do User fornecido como parâmetro
     * 
     * @return   (long)   A reputação do User 
     */
    public long getRep(){
        return this.rep;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o número de Questions do User fornecido como parâmetro
     * 
     * @return   (int)   O número de Questions do User 
     */
    public int getNumQues(){
        return this.numques;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o número de Answers do User fornecido como parâmetro
     * 
     * @return   (int)   O número de Answers do User 
     */
    public int getNumAns(){
        return this.numans;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece as Questions do User fornecido como parâmetro
     * 
     * @return   (Map<LocalDate,Questions>)   As Questions do User 
     */
    public List<Questions> getQues(){
        List<Questions> res = new ArrayList<> ();
        for(Questions q : ques){
            res.add(q);
        }
        return res;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece as Answers do User fornecido como parâmetro
     * 
     * @return   (Map<LocalDate,Answers>)   As Answers do User 
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
     * Set que fornece o Nome do User fornecido como parâmetro
     * 
     * @param   name   O novo Nome do User 
     */
    public void setName(String name){
        this.name = name;
    }
    //----------------------------------------------------------------------
    /**
     * Set que fornece o AboutMe do User fornecido como parâmetro
     * 
     * @param   aboutme   O novo AboutMe do User 
     */
    public void setAboutMe(String aboutme){
        this.aboutme = aboutme;
    }
    //----------------------------------------------------------------------
    /**
     * Set que fornece a Reputaçao do User fornecido como parâmetro
     * 
     * @param   rep   A nova Reputaçao do User 
     */
    public void setRep (long rep){
        this.rep = rep;
    }
    //----------------------------------------------------------------------
    /**
     * Set que fornece o Id do User fornecido como parâmetro
     * 
     * @param   id   O novo id do User 
     */
    public void setId (long id){
        this.id = id;
    }
    //----------------------------------------------------------------------
    /**
     * Set que fornece o Numero de Questions do User fornecido como parâmetro
     * 
     * @param   numques   O Numero de Questions do User 
     */
    public void setNumQues (int numques){
        this.numques = numques;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece o Numero de Answers do User fornecido como parâmetro
     * 
     * @param   numans   O Numero de Answers do User 
     */
    public void setNumAns (int numans){
        this.numans = numans;
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece as Questions do User fornecido como parâmetro
     * 
     * @param   f   As Questions do User 
     */
    public void setQues(List<Questions> ques){
        this.ques = new ArrayList<>(ques.size());
        ques.forEach (q -> this.ques.add(q));
    }
    //----------------------------------------------------------------------
    /**
     * Get que fornece as Answers do User fornecido como parâmetro
     * 
     * @param   f   As Answers do User 
     */
    public void setAns(List<Answers> ans){
        this.ans = new ArrayList<>(ans.size());
        ans.forEach (a -> this.ans.add(a));
    }
    //----------------------------------------------------------------------
    /**
     * Metodo clone da classe Users
     * 
     * @return  (Users)   Cópia do objeto Users
     */
    
    public Users clone(){
        return new Users(this);
    }
    
    /**
     * Metodo toString da classe Users
     * 
     * @return    (String)   String que representa a informaçao de um User
     */
    
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("Users{ Nome:");
        sb.append(this.getName());
        sb.append(", AboutMe:");
        sb.append(this.getAboutMe());
        sb.append(", Reputaçao:");
        sb.append(this.getRep());
        sb.append(", Id:");
        sb.append(this.getId());
        sb.append(", Numero de Questions:");
        sb.append(this.getNumQues());
        sb.append(", Numero de Answers:");
        sb.append(this.getNumAns());
        sb.append(", Questions:");
        sb.append(this.getQues());
        sb.append(", Answers:");
        sb.append(this.getAns());
        sb.append("}");
        return sb.toString();
    }
    
    /**
     *  Metodo equals da classe Users
     *  
     *  @param    o    Objeto a ser comparado
     *  
     *  @return    (boolean)   true se forem iguais false se nao o forem
     */
    
    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Users u = (Users) o;
        return  name.equals(u.getName()) && aboutme.equals(u.getAboutMe()) && u.getRep() == rep && u.getId() == id && u.getNumQues() == numques && u.getNumAns() == numans && ques.equals(u.getQues()) && ans.equals(u.getAns());
    }
}
