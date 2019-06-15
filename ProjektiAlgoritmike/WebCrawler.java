package seminar11;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import org.jsoup.*;
import org.jsoup.nodes.*;
import org.jsoup.select.*;
public class WebCrawler {
//	private int depth;
//	private String pathFile;
private String baseURL;
private static HashSet<String> containerURL;
private static int depth_max;
//private static BufferedWriter bw;
//private static int actual_depth;
//	public WebCrawler() {}
//	public WebCrawler(int d, String p, String b) {
//		depth = d;
//		pathFile = p;
//		baseURL = b;
//		containerURL = new HashSet<>();
//	}
	public static void getURLs(String url, int depth) throws IOException {
		if(url==null || url=="") {
			return;}
		if(!containerURL.contains(url) && depth<=depth_max) {
			try {
				String str = ">> Depth  " + depth + " [" + url + "]";
				writeToFile(str);
				System.out.println(str);
				containerURL.add(url);
				Document document =  Jsoup.connect(url).get();
				Elements linket =  document.select("a[href]");
				depth++;
				for (Element page : linket) {
                    getURLs(page.attr("abs:href"), depth);
                }
			}
			catch(IOException ex) {
				System.out.println("Error: "+ex.getMessage());
			}
		}
	}
	public static void writeToFile(String str) throws IOException {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter("C:/Users/Kevin Dule/Desktop/seminar10.txt",true));
		bw.write(str);
		bw.newLine();
		bw.close();
	}
		catch(IOException ex) {
			System.out.println("Ndodhi nje gabim!");
		}
	}
	public static void main(String[] args) throws IOException {
		containerURL = new HashSet<>();
		depth_max = 2;
		BufferedWriter bw = new BufferedWriter(new FileWriter("C:/Users/Kevin Dule/Desktop/seminar10.txt"));
		getURLs("https://google.com",0);

	}

}
