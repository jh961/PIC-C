package rs2321;

/*
 * rs2321.java
 *
 * 
 */

import java.io.*;


/**
 *
 * @author  Administrador
 */
public class rs2321 extends javax.swing.JFrame {

 

    WriterPort  emisor;
    ReaderPort  reader;
    String a ="",dato="",dato1="",tiempo1="00",person1="000",a1;
    char r,consul='D',borra='F';
    int ed,z,y;
    int tiempo=0,person;
    /** Creates new form rs2321 */
    public rs2321() {
        
        initComponents();
        
        this.emisor= WriterPort.getInstance();
        this.reader = ReaderPort.getInstance();

        this.reader.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                ActionEventPort actionEventPort = (ActionEventPort)evt;
                evento_de_Lectura(actionEventPort);
            }
        }
        );
        
               
        
    }
 
      public void evento_de_Lectura(ActionEventPort actionEventPort){
       
        a = a + actionEventPort.getReaded();
        ed = a.length();
      
        for (int i = 0; i < ed; i++) {

            r = a.charAt(i);
            if (r == '@') {
                z = i;

            } else if (r == ',') {
              y= ((Integer.parseInt(a.substring(i-2,i-1))*10)+(Integer.parseInt(a.substring(i-1,i))));
              
              
              if(y==43){
                  a1=a.substring(z,i-2);
                  a=a1+"On"+"\n"+a.substring(i+1);
              }else if(y==45){
                  a1=a.substring(z,i-2);
                  a=a1+"Off"+"\n"+a.substring(i+1);
              }else {
                 a1=a.substring(z,i-2);
                  a=a1+"00"+"\n"+a.substring(i+1);
              }
              
            }else if (r == '#') {
                
              
                dato = a.substring(z + 1, i);
                
                area1.setText("D / M / A / H / m /On-Off"+"\n"+dato);
                a = "";
            }
        
    
                
    
    
      
      }
      }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        boton_enviar = new javax.swing.JButton();
        caja1 = new javax.swing.JTextField();
        borrar = new javax.swing.JButton();
        jSeparator1 = new javax.swing.JSeparator();
        jScrollPane1 = new javax.swing.JScrollPane();
        area1 = new javax.swing.JTextArea();
        jLabel1 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        consultar = new javax.swing.JButton();
        jLabel6 = new javax.swing.JLabel();
        barra = new javax.swing.JScrollBar();
        temp = new java.awt.Label();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Plantilla Comunicaci�n RS-232");
        getContentPane().setLayout(null);

        boton_enviar.setText("Enviar");
        boton_enviar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                boton_enviarActionPerformed(evt);
            }
        });
        getContentPane().add(boton_enviar);
        boton_enviar.setBounds(290, 120, 80, 30);

        caja1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        caja1.setText("0");
        getContentPane().add(caja1);
        caja1.setBounds(110, 90, 50, 30);

        borrar.setText("Borrar");
        borrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                borrarActionPerformed(evt);
            }
        });
        getContentPane().add(borrar);
        borrar.setBounds(180, 490, 80, 30);
        getContentPane().add(jSeparator1);
        jSeparator1.setBounds(50, 240, 340, 10);

        area1.setColumns(20);
        area1.setRows(5);
        jScrollPane1.setViewportView(area1);

        getContentPane().add(jScrollPane1);
        jScrollPane1.setBounds(170, 270, 260, 150);

        jLabel1.setFont(new java.awt.Font("Arial Black", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(0, 0, 153));
        jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel1.setText("PROYECTO FINAL ");
        getContentPane().add(jLabel1);
        jLabel1.setBounds(60, 10, 330, 40);

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(153, 0, 0));
        jLabel3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel3.setText("Ingrese el # de Personas ");
        getContentPane().add(jLabel3);
        jLabel3.setBounds(60, 70, 170, 20);

        jLabel4.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(153, 0, 0));
        jLabel4.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel4.setText("Borrado de la EEPROM");
        getContentPane().add(jLabel4);
        jLabel4.setBounds(150, 460, 140, 20);

        jLabel5.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(153, 0, 0));
        jLabel5.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel5.setText("CONSULTAS EEPROM");
        getContentPane().add(jLabel5);
        jLabel5.setBounds(20, 260, 130, 20);

        consultar.setText("Consultar");
        consultar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                consultarActionPerformed(evt);
            }
        });
        getContentPane().add(consultar);
        consultar.setBounds(40, 290, 90, 90);

        jLabel6.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel6.setForeground(new java.awt.Color(153, 0, 0));
        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel6.setText("Tiempo ON/OFF MOTOR");
        getContentPane().add(jLabel6);
        jLabel6.setBounds(80, 130, 130, 20);

        barra.setMaximum(20);
        barra.setOrientation(javax.swing.JScrollBar.HORIZONTAL);
        barra.addAdjustmentListener(new java.awt.event.AdjustmentListener() {
            public void adjustmentValueChanged(java.awt.event.AdjustmentEvent evt) {
                barraAdjustmentValueChanged(evt);
            }
        });
        getContentPane().add(barra);
        barra.setBounds(30, 190, 380, 30);

        temp.setAlignment(java.awt.Label.CENTER);
        temp.setText("0");
        getContentPane().add(temp);
        temp.setBounds(70, 160, 130, 20);

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-456)/2, (screenSize.height-580)/2, 456, 580);
    }// </editor-fold>//GEN-END:initComponents

    private void borrarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_borrarActionPerformed

        borra='E';
        try {
        emisor.escribir("@"+person1+"$"+tiempo1+"&"+consul+"?"+borra+"#" );
        }
        catch(IOException iOException){
        }
        borra='F';


    }//GEN-LAST:event_borrarActionPerformed

    private void boton_enviarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_boton_enviarActionPerformed

        
        person1 = caja1.getText();
        person=Integer.parseInt(person1);
        if(person<=9){
             person1="0"+"0"+person1; 
        }else if((person>99)&&(person<999)){
            person1=person1;
        }else{
          person1="0"+person1;
        }
        try {
        emisor.escribir("@"+person1+"$"+tiempo1+"&"+consul+"?"+borra+"#" );
        }
        catch(IOException iOException){
        }
        
    }//GEN-LAST:event_boton_enviarActionPerformed

    private void barraAdjustmentValueChanged(java.awt.event.AdjustmentEvent evt) {//GEN-FIRST:event_barraAdjustmentValueChanged
   tiempo = barra.getValue();
   temp.setText(String.valueOf(tiempo));
   tiempo1=String.valueOf(tiempo);
   if(tiempo<=9){
   tiempo1="0"+tiempo1;
   
   }   
  
        // TODO add your handling code here:
    }//GEN-LAST:event_barraAdjustmentValueChanged

    private void consultarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_consultarActionPerformed
        area1.setText("");
        consul='C';
        try {
        emisor.escribir("@"+person1+"$"+tiempo1+"&"+consul+"?"+borra+"#" );
        }
        catch(IOException iOException){
        }
        consul='D';
        // TODO add your handling code here:
    }//GEN-LAST:event_consultarActionPerformed
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new rs2321().setVisible(true);
            }
        });
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextArea area1;
    private javax.swing.JScrollBar barra;
    private javax.swing.JButton borrar;
    private javax.swing.JButton boton_enviar;
    private javax.swing.JTextField caja1;
    private javax.swing.JButton consultar;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSeparator jSeparator1;
    private java.awt.Label temp;
    // End of variables declaration//GEN-END:variables
    
}