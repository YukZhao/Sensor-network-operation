import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class main {
    public static void main(String[]  args){
        int sum=0;
        int rmax=1;
        double[][] ps4 = new double[100][3];

        for(int r=0;r<rmax;r++){
            try {
                Scanner input = new Scanner(new File("data.txt"));
                for(int i=0;i<100;i++)
                    ps4[i][0]=input.nextDouble();
                for(int i=0;i<100;i++){
                    ps4[i][1]=input.nextDouble();
                   // System.out.println(i);
                    ps4[i][2]=0;
                }

                System.out.println(ps4);
                input.close();

            } catch (Exception e) {
                System.out.println("读取文件内容出错");
                e.printStackTrace();
            }

            double BSx=50;
            double BSy=300;
            int node=100;
            double tx,ty;
            for(int i=0;i<node;i++){
                for(int j=i;j<node;j++){
                    if((Math.pow(ps4[i][0]-BSx,2)+Math.pow(ps4[i][1]-BSy,2))>(Math.pow(ps4[j][0]-BSx,2)+Math.pow(ps4[j][1]-BSy,2))){
                        tx=ps4[i][0];
                        ty=ps4[i][1];
                        ps4[i][0]=ps4[j][0];
                        ps4[i][1]=ps4[j][1];
                        ps4[j][0]=tx;
                        ps4[j][1]=ty;
                    }
                }
                ps4[i][2]=i;
            }
            System.out.println("ps4排序后为\n"+ps4);
            double[][] d=new double[100][100];
            for (int i=0;i<node;i++){
                for(int j=0;j<node;j++){
                    if(i!=j){
                        d[i][j]=Math.sqrt(Math.pow((ps4[i][0]-ps4[j][0]),2)+Math.pow((ps4[i][1]-ps4[j][1]),2));
                    }
                    else
                        d[i][j]=100000000.0;
                }
            }
            int indx=node-1;
            double totaldis=0;
            double[][] ps5=new double[100][3];
            double distance;
            double min;
            int min_i;
            for(int i=0;i<node;i++){
                ps5[i]=ps4[indx];
                for(int j=0;j<node;j++){
                    d[j][indx]=100000000.0;
                }
                min=d[indx][0];
                min_i=0;
                for(int j=1;j<node;j++){
                    if(min>d[indx][j]){
                        min=d[indx][j];
                        min_i=j;
                    }
                }
                indx=min_i;
                if((int)min!=100000000)totaldis=totaldis+min*min;
            }
            System.out.println("totaldis="+totaldis);
            System.out.println("ps5排序后为\n"+ps5);
            double costofdirectn=0;
            for(int i=0;i<node;i++){
                costofdirectn=costofdirectn+Math.pow(ps4[i][0]-BSx,2)+Math.pow(ps4[i][1]-BSy,2);
            }
            double costofpegasisn=totaldis*node+costofdirectn;
            double costofpegasis=costofpegasisn/node;
            System.out.println("costofpegasisn="+costofpegasisn);
            System.out.println("costofpegasis="+costofpegasis);
            System.out.println("输出路线图");
            for(int i=0;i<node;i++){
                System.out.println("("+ps5[i][0]+","+ps5[i][1]+")->");
            }
        }
    }

}
