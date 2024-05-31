package rs2321;

/*
 * ActionEventPort.java
 *
 * 
 */

/**
 *
 * 
 */
public class ActionEventPort extends java.awt.event.ActionEvent {

    private String readed;
    
    /** Creates a new instance of ActionEventPort */
    public ActionEventPort(Object source, int id, String command, String readed) {
        super(source, id, command);
        this.readed = readed/* + "gato"*/;
        System.out.println("Caracter : "+ readed);
        //System.out.println("Caracter : "+readed+" Valor : "+ (new Character(readed.charAt(0)).hashCode() ));
    }
    
    public String getReaded()
    {
        return this.readed;
    }
    
}
