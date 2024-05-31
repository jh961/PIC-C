package rs2321;

/*
 * rs2321.java
 *
 *
 */
import java.io.*;

/**
 *
 * @author Administrador
 */
public class rs2321 extends javax.swing.JFrame {

    WriterPort emisor;
    ReaderPort reader;
    String a = "";
    int ed;
    char r;

    /**
     * Creates new form rs2321
     */
    public rs2321() {

        initComponents();

        this.emisor = WriterPort.getInstance();
        this.reader = ReaderPort.getInstance();

        this.reader.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ActionEventPort actionEventPort = (ActionEventPort) evt;
                evento_de_Lectura(actionEventPort);
            }
        });



    }

    public void evento_de_Lectura(ActionEventPort actionEventPort) {

       
        
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        enviar = new javax.swing.JButton();
        caja1 = new javax.swing.JTextField();
        borrar = new javax.swing.JButton();
        jSeparator1 = new javax.swing.JSeparator();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        barra = new javax.swing.JScrollBar();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Plantilla Comunicación RS-232");
        getContentPane().setLayout(null);

        enviar.setText("Enviar");
        enviar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                enviarActionPerformed(evt);
            }
        });
        getContentPane().add(enviar);
        enviar.setBounds(80, 250, 80, 30);

        caja1.setText("800");
        getContentPane().add(caja1);
        caja1.setBounds(120, 110, 170, 30);

        borrar.setText("Borrar");
        borrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                borrarActionPerformed(evt);
            }
        });
        getContentPane().add(borrar);
        borrar.setBounds(240, 250, 80, 30);
        getContentPane().add(jSeparator1);
        jSeparator1.setBounds(40, 50, 340, 10);

        jLabel1.setFont(new java.awt.Font("Arial Black", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(0, 0, 153));
        jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel1.setText("ENVIO DE DATOS MODULACION AC");
        getContentPane().add(jLabel1);
        jLabel1.setBounds(40, 10, 330, 40);

        jLabel2.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(153, 0, 0));
        jLabel2.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel2.setText("ON");
        getContentPane().add(jLabel2);
        jLabel2.setBounds(340, 140, 30, 20);

        barra.setBlockIncrement(0);
        barra.setMaximum(800);
        barra.setOrientation(javax.swing.JScrollBar.HORIZONTAL);
        barra.setToolTipText("");
        barra.setVisibleAmount(0);
        barra.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        barra.addAdjustmentListener(new java.awt.event.AdjustmentListener() {
            public void adjustmentValueChanged(java.awt.event.AdjustmentEvent evt) {
                barraAdjustmentValueChanged(evt);
            }
        });
        getContentPane().add(barra);
        barra.setBounds(30, 170, 350, 40);

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(153, 0, 0));
        jLabel3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel3.setText("DATO A ENVIAR");
        getContentPane().add(jLabel3);
        jLabel3.setBounds(130, 70, 140, 20);

        jLabel4.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(153, 0, 0));
        jLabel4.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel4.setText("OFF");
        getContentPane().add(jLabel4);
        jLabel4.setBounds(60, 140, 30, 20);

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-417)/2, (screenSize.height-344)/2, 417, 344);
    }// </editor-fold>//GEN-END:initComponents

    private void borrarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_borrarActionPerformed

        a = "";
        caja1.setText("800");
        barra.setValue(0);


    }//GEN-LAST:event_borrarActionPerformed

    private void enviarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_enviarActionPerformed


        try {

            String datos1;
            int dato;
            
            datos1 = caja1.getText();
            dato= Integer.parseInt(datos1);
            
            if(dato<=9){
                emisor.escribir("@" +"0"+"0"+ datos1 + "#");
            }else if((dato>9)&&(dato<=99)){
                emisor.escribir("@" +"0"+ datos1 + "#");
            }else {
                emisor.escribir("@" + datos1 + "#");
            }
            
        } catch (IOException iOException) {
        }

// TODO add your handling code here:
    }//GEN-LAST:event_enviarActionPerformed

    private void barraAdjustmentValueChanged(java.awt.event.AdjustmentEvent evt) {//GEN-FIRST:event_barraAdjustmentValueChanged
        
        caja1.setText(String.valueOf((800-barra.getValue())));
    }//GEN-LAST:event_barraAdjustmentValueChanged

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
    private javax.swing.JScrollBar barra;
    private javax.swing.JButton borrar;
    private javax.swing.JTextField caja1;
    private javax.swing.JButton enviar;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JSeparator jSeparator1;
    // End of variables declaration//GEN-END:variables
}
