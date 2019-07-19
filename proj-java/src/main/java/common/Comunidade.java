package common;

import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.lang.String;
import java.time.LocalDate;
import java.util.TreeMap;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Comparator;
/**
 * Write a description of class Comunidade here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Comunidade
{
    /**
     * HashMap de valor Users e key o seu Id
     */
    private Map<Long,Users> HTU;
    /**
     * HashMap de valor Questions e key o seu Id
     */
    private Map<Long,Questions> HTQ;
    /**
     * HashMap de valor Answers e key o seu Id
     */
    private Map<Long,Answers> HTA;
    /**
     * HashMap de valor String (TagName das Tags) e key do Id das Tags
     */
    private Map<String,Long> HTT;

    /**
     * Construtor vazio da classe Comunidade
     */
    public Comunidade(){
        this.HTU = new HashMap<>();
        this.HTQ = new HashMap<>();
        this.HTA = new HashMap<>();
        this.HTT = new HashMap<>();
    }
    //________________________________________________________________________
    /**
     * Construtor parameterizado da classe Comunidade
     * 
     * @param HTU   HashMap de valor Users e key o seu Id
     * @param HTQ   HashMap de valor Questions e key o seu Id
     * @param HTA   HashMap de valor Answers e key o seu Id
     * @param HTT   HashMap de valor String (TagName das Tags) e key do Id das Tags
     */
    public Comunidade(Map<Long,Users> HTU,Map<Long,Questions> HTQ,Map<Long,Answers> HTA,Map<String,Long> HTT){
        this.setHTU(HTU);
        this.setHTQ(HTQ);
        this.setHTA(HTA);
        this.setHTT(HTT);
    }
    //________________________________________________________________________
    /**
     * Construtor copia da classe Comunidade
     * 
     * @param   c   Comunidade
     */    
    public Comunidade(Comunidade c){
        this.HTU = c.getHTU();
        this.HTQ = c.getHTQ();
        this.HTA = c.getHTA();
        this.HTT = c.getHTT();
    }
    //________________________________________________________________________
    /**
     * Get do HTU
     * 
     * @return  (Map<Long,Users>)  HashMap de Users
     */
    public Map<Long,Users> getHTU(){
        Map<Long,Users> res = new HashMap<>();
        for(Long s : this.HTU.keySet()){
            res.put(s,this.HTU.get(s));
        }
        return res;
    }
    //________________________________________________________________________
    /**
     * Get do HTQ
     * 
     * @return  (Map<Long,Questions>)  HashMap de Questions
     */
    public Map<Long,Questions> getHTQ(){
        Map<Long,Questions> res = new HashMap<>();
        for(Long s : this.HTQ.keySet()){
            res.put(s,this.HTQ.get(s));
        }
        return res;
    }
    //________________________________________________________________________
    /**
     * Get do HTA
     * 
     * @return  (Map<Long,Answers>)  HashMap de Answers
     */
    public Map<Long,Answers> getHTA(){
        Map<Long,Answers> res = new HashMap<>();
        for(Long s : this.HTA.keySet()){
            res.put(s,this.HTA.get(s));
        }
        return res;
    }
    //________________________________________________________________________
    /**
     * Get do HTT
     * 
     * @return  (Map<Long,String>)  HashMap de Tags
     */
    public Map<String,Long> getHTT(){
        Map<String,Long> res = new HashMap<>();
        for(String s : this.HTT.keySet()){
            res.put(s,this.HTT.get(s));
        }
        return res;
    }
    //________________________________________________________________________
    /**
     * Set do HTU
     * 
     * @param  Novo HashMap de Users
     */
    public void setHTU(Map<Long,Users> f){
        this.HTU= new HashMap<>();
        for(Long s :f.keySet()){
            Users e =f.get(s).clone();
            this.HTU.put(s,e);
        }
    }
    //________________________________________________________________________
    /**
     * Set do HTQ
     * 
     * @param  HashMap de Questions
     */
    public void setHTQ(Map<Long,Questions> f){
        this.HTQ= new HashMap<>();
        for(Long s :f.keySet()){
            Questions e =f.get(s).clone();
            this.HTQ.put(s,e);
        }
    }
    //________________________________________________________________________
    /**
     * Get do HTA
     * 
     * @param  HashMap de Answers
     */
    public void setHTA(Map<Long,Answers> f){
        this.HTA= new HashMap<>();
        for(Long s :f.keySet()){
            Answers e =f.get(s).clone();
            this.HTA.put(s,e);
        }
    }
    //________________________________________________________________________
    /**
     * Get do HTT
     * 
     * @param  HashMap de Tags
     */
    public void setHTT(Map<String,Long> f){
        this.HTT = new HashMap<>();
        for(String s :f.keySet()){
            Long e =f.get(s);
            this.HTT.put(s,e);
        }
    }
    //________________________________________________________________________
    /**
     * Funçao que transforma uma string tags num arraylist de tags
     * 
     * @param   tags    String que contem todas as Tags
     * 
     * @return   (ArrayList<String>)   ArrayList de Strings em que cada String e uma Tag
     */
    public List<String> toAL(String tags){
        StringBuilder a = new StringBuilder(tags);
        if(a.length() == 0) return new ArrayList<>();
        a.deleteCharAt(0);
        a.deleteCharAt(a.length() - 1);
        String strMain = a.toString();
        //System.out.println(strMain);
        String[] arrSplit = strMain.split("><");
        List<String> ar = new ArrayList<>();
        for(String s : arrSplit){
            if(s.length() != 0)
                ar.add(s);
        }
        return ar;
    }
    //________________________________________________________________________
    /**
     * Funçao que converte a string num LocalDate
     * 
     * @param   data    Uma String que contem os valores de uma data
     * 
     * @return   (LocalDate)   Essa mesma data em LocalDate
     */
    public LocalDate convert(String data){        
        String year = data.substring(0,4);
        String month = data.substring(5,7);
        String day = data.substring(8,10);
        int ano = Integer.parseInt(year);
        int mes = Integer.parseInt(month);
        int dia = Integer.parseInt(day);
        LocalDate newdata = LocalDate.of(ano,mes,dia);
        return newdata;
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona um User ao HashMap de Users
     * 
     * @param   name    Nome do User
     * @param   aboutme     AboutMe do User
     * @param   rep     Reputaçao do User
     * @param   id    Id do User
     */
    public void addUser(String name, String aboutme, long rep, long id){
        Users u = new Users();
        u.setName(name);
        u.setAboutMe(aboutme);
        u.setRep(rep);
        u.setId(id);
        u.setNumAns(0);
        u.setNumQues(0);
        u.setAns(new ArrayList <>());
        u.setQues(new ArrayList <>());
        HTU.put(id,u);
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Tag ao HashMap de Tags
     * 
     * @param   id    Id da Tag
     * @param   tagname    Nome da Tag
     */
    public void addTag(long id, String tagname){
        HTT.put(tagname,id);
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Question ao HashMap de Questions
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   tags    Lista com as tags da Question
     * @param   title    Titulo da Question
     * @param   anscount    Numero de Answers que respondem a Question
     */
    public void addQuestion(long id, LocalDate data, long owneruserid, List<String> tags, String title,int anscount){
        if(!HTQ.containsKey(id)){
            Questions q = new Questions();
            q.setId(id);
            q.setData(data);
            q.setOwneruserid(owneruserid);
            q.setTags(tags);
            q.setNumtags(tags.size());
            q.setTitle(title);
            q.setAnscount(anscount);
            q.setAns(new ArrayList <>());
            HTQ.put(id,q);
        }
        else{
            Questions q1 = HTQ.get(id);
            q1.setData(data);
            q1.setOwneruserid(owneruserid);
            q1.setTags(tags);
            q1.setNumtags(tags.size());
            q1.setTitle(title);
            q1.setAnscount(anscount);
        }
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Question ao ArrayList de Questions no User, feitas todas pelo User que fez esta Question
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   tags    Lista com as tags da Question
     * @param   title    Titulo da Question
     * @param   anscount    Numero de Answers que respondem a Question
     */
    public void addQuestionToUser(long id, LocalDate data, long owneruserid, List<String> tags, String title,int anscount){
        Users u = HTU.get(owneruserid);
        u.setNumQues(u.getNumQues() + 1);
        Questions q = new Questions();
        q.setId(id);
        q.setData(data);
        q.setOwneruserid(owneruserid);
        q.setTags(tags);
        q.setNumtags(tags.size());
        q.setTitle(title);
        q.setAnscount(anscount);
        q.setAns(new ArrayList <>());
        List<Questions> a = u.getQues();
        a.add(q);
        u.setQues(a);
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Answer ao HashMap de Answers
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   parentid    Id da Question a que esta Answer responde
     * @param   score    Score da Answer
     * @param   comcount    Numero de Comments da Answer
     */
    public void addAnswer(long id, LocalDate data, long owneruserid, long parentid, int score, int comcount){
        Answers a = new Answers();
        a.setId(id);
        a.setData(data);
        a.setOwneruserid(owneruserid);
        a.setParentid(parentid);
        a.setScore(score);
        a.setComcount(comcount);
        HTA.put(id,a);
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Answer ao ArrayList de Answers no User, feitas todas pelo User que fez esta Answer
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   parentid    Id da Question a que esta Answer responde
     * @param   score    Score da Answer
     * @param   comcount    Numero de Comments da Answer
     */
    public void addAnswerToUser(long id, LocalDate data, long owneruserid, long parentid, int score, int comcount){
        Users u = HTU.get(owneruserid);
        u.setNumAns(u.getNumAns() + 1);
        Answers a = new Answers();
        a.setId(id);
        a.setData(data);
        a.setOwneruserid(owneruserid);
        a.setParentid(parentid);
        a.setScore(score);
        a.setComcount(comcount);
        List<Answers> alist = u.getAns();
        alist.add(a);
        u.setAns(alist);
    }
    //________________________________________________________________________
    /**
     * Funçao que adiciona uma Answer ao ArrayList de Answers na Question, feitas todas para responder a mesma Question
     * 
     * @param   id    Id da Question
     * @param   data    Data de criaçao da Question
     * @param   owneruserid    Id do criador da Question
     * @param   parentid    Id da Question a que esta Answer responde
     * @param   score    Score da Answer
     * @param   comcount    Numero de Comments da Answer
     */
    public void addAnswerToQuestion(long id, LocalDate data, long owneruserid, long parentid, int score, int comcount){
        if(!HTQ.containsKey(parentid)){
            addQuestion(parentid, LocalDate.of(1,1,1), 0, new ArrayList<>(), "", 0);
        }
        Questions q = HTQ.get(parentid);
        Answers a = new Answers();
        a.setId(id);
        a.setData(data);
        a.setOwneruserid(owneruserid);
        a.setParentid(parentid);
        a.setScore(score);
        a.setComcount(comcount);
        List<Answers> alist = q.getAns();
        alist.add(a);
        q.setAns(alist);
    }    
    //________________________________________________________________________
    /**Função que verifica se uma string esta contida noutra

     * @param Duas strings

     * @return (boolean) 1 se está contida, 0 se não está
     */
    public boolean isThere(String grande,String palavra){
        if (grande.equals("") || palavra.equals(""))
            return false;
        String[] algo = grande.split("\\s+|(?=\\p{Punct})|(?<=\\p{Punct})");
        boolean ret = false;
        for(int i=0;i<algo.length;i++){
            String a = algo[i];
            if(palavra.compareTo(a) == 0){
                ret=true;
            }
        }
        return ret;
    }
    //________________________________________________________________________
    /**
     * Funçao que organiza as tags por ordem decrescente de quantidade existente
     * 
     * @param Um Map desorganizado
     * 
     * @return (Map<String,Integer>) Um Map organizado
     */
    
    public Map<String,Integer> sortTags(Map<String,Integer> unsortMap){
        List<Entry<String,Integer>> list = new LinkedList<Entry<String,Integer>>(unsortMap.entrySet());
        Collections.sort(list, new Comparator<Entry<String,Integer>>(){
            public int compare(Entry<String,Integer> o1,Entry<String,Integer> o2){
                if(o1.getValue()<o2.getValue())
                    return 1;
                else if(o1.getValue()>o2.getValue()){
                    return -1;
                }
                else{
                    return 0;
                }
            }
        });
        Map<String,Integer> sortedMap = new LinkedHashMap<String,Integer>();
        for (Entry<String,Integer> entry : list){
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }
    //________________________________________________________________________
    /**
     * Metodo clone da classe Comunidade
     * 
     * @return   (Comunidade)   clone da Comunidade
     */
    public Comunidade clone(){
        return new Comunidade(this);
    }
    
    /**
     * Metodo toString da classe Comunidade
     * 
     * @return   (String)   String com a informaçao da classe Comunidade
     */
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("Empresas{ Informacao sobre a HashTable dos Users:");
        sb.append(this.getHTU());
        sb.append(", Informacao sobre a HashTable das Questions:");
        sb.append(this.getHTQ());
        sb.append(", Informacao sobre a HashTable das Answers:");
        sb.append(this.getHTA());
        sb.append(", Informacao sobre a HashTable das Tags:");
        sb.append(this.getHTT());
        sb.append("}");
        return sb.toString();
    }
    
    /**
     *  Metodo equals da classe Comunidade
     *  
     *  @param o    Objeto a ser comparado
     *  @return (boolean)   true se forem iguais false se nao o forem
     */
    
    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Comunidade c = (Comunidade) o;
        return HTU.equals(c.getHTU()) && HTQ.equals(c.getHTQ()) && HTA.equals(c.getHTA()) && HTT.equals(c.getHTT());
    }

    public void clearCom(){
        HTU.clear();
        HTQ.clear();
        HTA.clear();
        HTT.clear();
    }
}
