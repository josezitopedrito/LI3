package engine;

import java.util.Map;
import java.util.HashMap;
import java.time.LocalDate;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;
import java.lang.StringBuffer;
import java.lang.String;

import common.Pair;
import common.Answers;
import common.Comunidade;
import engine.ParserPosts;
import engine.ParserUsers;
import engine.ParserTags;
import common.Posts;
import common.Questions;
import common.Users;
import li3.TADCommunity;

/**
 * Write a description of class TCDExample here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class TCDExample implements TADCommunity
{
	private Comunidade c;

    public void load(String dump){
        c = new Comunidade();
        StringBuilder sb1 = new StringBuilder(dump);
        StringBuilder sb2 = new StringBuilder(dump);
        StringBuilder sb3 = new StringBuilder(dump);
        ParserUsers pu = new ParserUsers();
        ParserPosts pp = new ParserPosts();
        ParserTags pt = new ParserTags();
        String u = sb1.append("/Users.xml").toString();
        String p = sb2.append("/Posts.xml").toString();
        String t = sb3.append("/Tags.xml").toString();
        c = pu.functionU(c,u);
        c = pp.functionP(c,p);
        c = pt.functionT(c,t);
    }
    
    public Pair<String,String> infoFromPost(long id){
        Pair p = new Pair<String,String>("","");
        if(c.getHTQ().containsKey(id)){
            Questions q = c.getHTQ().get(id);
            Long idU = q.getOwneruserid();
            String titulo = q.getTitle();
            Users u = c.getHTU().get(idU);
            String nome = u.getName();
            p.setFst(titulo);
            p.setSecond(nome);
        }
        else if (c.getHTA().containsKey(id)){
            Answers a = c.getHTA().get(id);
            long idQ = a.getParentid();
            Questions q = c.getHTQ().get(idQ);
            Long idU = q.getOwneruserid();
            String titulo = q.getTitle();
            Users u = c.getHTU().get(idU);
            String nome = u.getName();
            p.setFst(titulo);
            p.setSecond(nome);
        }
        else {
            p.setFst("");
            p.setSecond("");
        }
        return p;
    }
    
    public List<Long> topMostActive(int N){
        int i;
        List<Long> l = new ArrayList<>();
        List<Users> other = new ArrayList<>();
        Map<Long,Users> HTU = c.getHTU();
        for(Users u : HTU.values()){
            other.add(u);
        }
        Comparator<Users> comp = (a,b) -> {
            if((a.getNumAns() + a.getNumQues()) > (b.getNumAns() + b.getNumQues()))
                return -1;
            else if((a.getNumAns() + a.getNumQues()) < (b.getNumAns() + b.getNumQues())){
                return 1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        for(i = 0;(i < N) && (i<other.size()); i++){
            l.add(i,other.get(i).getId());
        }
        
        return l;
    }
    
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        Pair p = new Pair<Long,Long>((long)0, (long)0);
        int ques = 0;
        int ans = 0;
        Map<Long,Questions> HTQ = c.getHTQ();
        Map<Long,Answers> HTA = c.getHTA();
        for(Questions q : HTQ.values()){
            if((q.getData().isBefore(end) || q.getData().isEqual(end)) && (q.getData().isAfter(begin) || q.getData().isEqual(begin))){
                ques++;
            }
        }
        p.setFst(ques);
        for(Answers a : HTA.values()){
            if((a.getData().isBefore(end) || a.getData().isEqual(end)) && (a.getData().isAfter(begin) || a.getData().isEqual(begin))){
                ans++;
            }
        }
        p.setSecond(ans);   

        return p;  
    }
    
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List<Long> l = new ArrayList<>();
        List<Questions> other = new ArrayList<>();
        Map<Long,Questions> HTQ = c.getHTQ();
        for(Questions q : HTQ.values()){
            if((q.getData().isBefore(end)) && (q.getData().isAfter(begin))){
                for(String s : q.getTags()){
                    if(tag.equals(s)){
                        other.add(q);
                    }
                }
            }
        }
        
        Comparator<Questions> comp = (a,b) -> {
            if(a.getData().isBefore(b.getData()))
                return 1;
            else if(a.getData().isAfter(b.getData())){
                return -1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        int i;
        for(i = 0;i < (other.size()); i++){
            l.add(i,other.get(i).getId());
        }
        
        return l;
    }
    
    public Pair<String, List<Long>> getUserInfo(long id){
       Pair p = new Pair<String, List<Long>>("",new ArrayList<>());
       if(!c.getHTU().containsKey(id)){
           return p;
       }
       Users u = c.getHTU().get(id);
       String abtme = u.getAboutMe();
       List<Long> ph = new ArrayList<>();
       List<Questions> qa = u.getQues();
       List<Answers> aa = u.getAns();
       Comparator<Questions> compq = (a,b) -> {
            if(a.getData().isBefore(b.getData()))
                return 1;
            else if(a.getData().isAfter(b.getData())){
                return -1;
            }
            else{
                return 0;
            }
        };
       qa.sort(compq);
       Comparator<Answers> compa = (a,b) -> {
            if(a.getData().isBefore(b.getData()))
                return 1;
            else if(a.getData().isAfter(b.getData())){
                return -1;
            }
            else{
                return 0;
            }
        };
       aa.sort(compa);
       int j=0,k=0;
       while((j+k<((qa.size())+(aa.size())))&&(ph.size()<10)){
           if(j<(qa.size()) && k<(aa.size()) && qa.get(j).getData().isAfter(aa.get(k).getData())){
               ph.add(qa.get(j).getId());
               j++;
            }
            else if(j<(qa.size()) && k<(aa.size()) && aa.get(k).getData().isAfter(qa.get(j).getData())){
                ph.add(aa.get(k).getId());
                k++;
            }
            else{
                if(j<(qa.size())){
                    ph.add(qa.get(j).getId());
                    j++;
                }
                else{
                    ph.add(aa.get(k).getId());
                    k++;
                }
           }
       }
       p.setFst(abtme);
       p.setSecond(ph);

       return p;
    }
    
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        List<Long> l = new ArrayList<>();
        List<Answers> other = new ArrayList<>();
        Map<Long,Answers> HTA = c.getHTA();
        for(Answers q : HTA.values()){
            if((q.getData().isBefore(end)) && (q.getData().isAfter(begin))){
                other.add(q);
            }
        }
        Comparator<Answers> comp = (a,b) -> {
            if(a.getScore()<b.getScore())
                return 1;
            else if(a.getScore()>b.getScore()){
                return -1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        
        int i;
        for(i = 0;i < N; i++){
            l.add(i,other.get(i).getId());
        }

        return l;
    }
    
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        List<Long> l = new ArrayList<>();
        List<Questions> other = new ArrayList<>();
        for(Questions q : c.getHTQ().values()){
            if((q.getData().isBefore(end)) && (q.getData().isAfter(begin))){
                other.add(q.clone());
            }
        }
        
        for(Questions q : other){
            for(Answers a : q.getAns()){
                if((!a.getData().isBefore(end)) || (!a.getData().isAfter(begin))){
                    q.setAnscount(q.getAnscount() - 1);
                }
            }
        }
        
        Comparator<Questions> comp = (a,b) -> {
            if(a.getAnscount()<b.getAnscount())
                return 1;
            else if(a.getAnscount()>b.getAnscount()){
                return -1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        int i;
        for(i = 0;(i < N) && (i<other.size()); i++){
            l.add(i,other.get(i).getId());
        }
        
        return l;
    }
    
    public List<Long> containsWord(int N, String word){
        List<Long> l = new ArrayList<>();
        List<Questions> other = new ArrayList<>();
        Map<Long,Questions> HTQ = c.getHTQ();
        while(other.size() <= N){
            for(Questions q : HTQ.values()){
                if(c.isThere(q.getTitle(), word)){
                    other.add(q);
                }
            }
        }
        
        Comparator<Questions> comp = (a,b) -> {
            if(a.getData().isBefore(b.getData()))
                return 1;
            else if(a.getData().isAfter(b.getData())){
                return -1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        int i;
        for(i = 0;(i < N) && (i<other.size()); i++){
            l.add(i,other.get(i).getId());
        }
        
        return l;
    }
    
    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> l = new ArrayList<>();
        List<Questions> other = new ArrayList<>();
        Map<Long,Users> HTU = c.getHTU();
        if(!HTU.containsKey(id1) || !HTU.containsKey(id2)){
            System.out.println("Um dos Users ou ambos nao existe");
            return l;
        }
        //id1 question, id2 answer
        for(Questions q : HTU.get(id1).getQues()){
            for(Answers a : HTU.get(id2).getAns()){
                if(q.getId() == a.getParentid()){
                    other.add(q);
                    break;
                }
            }
        }
        //id2 question, id2 answer
        for(Questions q : HTU.get(id2).getQues()){
            for(Answers a : HTU.get(id1).getAns()){
                if(q.getId() == a.getParentid()){
                    other.add(q);
                    break;
                }
            }
        }
        //id1 answer, id2 answer
        for(Answers a1 : HTU.get(id1).getAns()){
            for(Answers a2 : HTU.get(id2).getAns()){
                if(a1.getParentid() == a2.getParentid()){
                    other.add(c.getHTQ().get(a1.getParentid()));
                    break;
                }
            }
        }
        
        Comparator<Questions> comp = (a,b) -> {
            if(a.getData().isBefore(b.getData()))
                return 1;
            else if(a.getData().isAfter(b.getData())){
                return -1;
            }
            else{
                return 0;
            }
        };
        other.sort(comp);
        int i;
        for(i = 0;(i < N) && (i<other.size()); i++){
            if(!l.contains(other.get(i).getId()))
                l.add(i,other.get(i).getId());
        }
        
        return l;
    }
    
    public long betterAnswer(long id){
        Questions q = c.getHTQ().get(id);
        double valor;
        double ansvalue = 0;
        long amax = 0;
        for(Answers a : q.getAns()){
            Users u = c.getHTU().get(a.getOwneruserid());
            valor = ((double)a.getScore() * 0.65) + ((double)u.getRep() * 0.25) + ((double)a.getComcount() * 0.1);
            if(valor > ansvalue){
                ansvalue = valor;
                amax = a.getId();
            }
        }

        return amax;
    }
    
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<Users> users = new ArrayList<>();
        List<Users> novo = new ArrayList<>();
        Map<String,Long> HTT = c.getHTT();
        Map<String,Integer> tags = new HashMap<>();
        Map<Long,Users> HTU = c.getHTU();
        for(Users u1 : HTU.values()){
            users.add(u1);
        }        
        Comparator<Users> comp = (a,b) -> {
            if(a.getRep()<b.getRep())
                return 1;
            else if(a.getRep()>b.getRep()){
                return -1;
            }
            else{
                return 0;
            }
        };
        users.sort(comp);
        int i;
        for(i = 0;(i < N) && (i < users.size()); i++){
            novo.add(users.get(i));
        }
        
        for(Users u : novo){
            for(Questions q : u.getQues()){
                if((q.getData().isBefore(end) || q.getData().isEqual(end)) && (q.getData().isAfter(begin)  || q.getData().isEqual(begin))){
                    for(String t : q.getTags()){
                        if(!tags.containsKey(t)){
                            tags.put(t,1);
                        }
                        else{
                            int val = tags.get(t);
                            tags.remove(t);
                            tags.put(t,val+1);
                        }
                    }
                }
            }
        }
        
        tags = c.sortTags(tags);
        
        List<String> tags2 = new ArrayList<>(tags.keySet());
        List<Long> idt = new ArrayList<>();
        for(i = 0; (i < N) && (i < tags.size());i++){
            idt.add(i,HTT.get(tags2.get(i)));
        }
        return idt;       
    }

    public void clear(){
    	c.clearCom();
    }
}
