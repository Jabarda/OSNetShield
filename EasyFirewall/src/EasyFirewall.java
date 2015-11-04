import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;

/**
 * Created by 1 on 03.11.2015.
 */
public class EasyFirewall {

    public static void main(String[] args) {
        JFrame window = new JFrame("EasyFirewall");
        window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        window.setLayout(new GridLayout());
        window.setSize(500, 500);
        JButton close = new JButton(); //закрывает
        close.setText("Close Ethernet");
        JButton open = new JButton();  //открывает
        open.setText("Open Ethernet");
        close.addMouseListener(new MouseListener() {

            public void mouseClicked(MouseEvent event) {
                try {
                    Runtime.getRuntime().exec("netsh advfirewall set allprofiles firewallpolicy blockinbound,blockoutbound");
                } catch (IOException e) {
                    e.printStackTrace();
                };
            }

            public void mouseEntered(MouseEvent event) {
            }

            public void mouseExited(MouseEvent event) {
            }

            public void mousePressed(MouseEvent event) {
            }

            public void mouseReleased(MouseEvent event) {
            }

        });
        open.addMouseListener(new MouseListener() {

            public void mouseClicked(MouseEvent event) {
                try {
                    Runtime.getRuntime().exec("netsh advfirewall set allprofiles firewallpolicy blockinbound,allowoutbound");
                } catch (IOException e) {
                    e.printStackTrace();
                };
            }

            public void mouseEntered(MouseEvent event) {
            }

            public void mouseExited(MouseEvent event) {
            }

            public void mousePressed(MouseEvent event) {
            }

            public void mouseReleased(MouseEvent event) {
            }

        });

        window.add(open);
        window.add(close);
        window.setVisible(true);
    }
}
