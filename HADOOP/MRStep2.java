package MRStep2;

import java.io.IOException;
import java.util.*;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.Mapper.Context;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
public class MRStep2{
	public static StringBuilder sb = new StringBuilder();
	public static ArrayList<String> arr = new ArrayList<String>();
	public static String actor = "";
	
	public static class Map
	extends Mapper <LongWritable, Text, Text, Text>{

		private Text movie = new Text();
		
		@Override
		public void map(LongWritable key, Text value, Context context
				) throws IOException, InterruptedException {
			arr.clear();
			StringTokenizer itr = new StringTokenizer(value.toString(), ";");
			movie.set(itr.nextToken());

			while (itr.hasMoreTokens()) {
				actor = itr.nextToken().trim();
				if (actor != "" && actor != ";" && actor != ";;" && actor != ";;;")
					arr.add(actor);
			}
			
			for ( int x1 = 0; x1 < arr.size(); x1++) {
				Text actor1 = new Text();
				actor1.set(arr.get(x1).trim());
				sb.setLength(0);
				for ( int x2 = 0; x2 < arr.size(); x2++ ) {
					if ( x1 != x2) {
						sb.append(arr.get(x2));
						sb.append(",");
					}
				}
				Text actor2 = new Text();
				actor2.set(sb.toString());
				context.write(actor1, actor2);
			}
		}
	}
	

	public static class Reduce
	extends Reducer<Text,Text,Text,Text> {

		@Override
		public void reduce(Text key, Iterable<Text> values,
				Context context
				) throws IOException, InterruptedException {
			
			Text result = new Text();
			String str ="";
			for (Text val: values) {
				str = str + val.toString()+ "\t";
			}
			result.set(str);
			context.write(key, result);
		}
	}

	public static void main(String[] args) throws Exception {
		if (args.length != 2)
	    {
	      System.err.println("Usage: wordmean <in> <out>");
	    }

		Configuration conf = new Configuration();
		conf.set("mapreduce.map.output.compress", "true");
		conf.set("mapreduce.output.fileoutputformat.compress", "false");
		Job job = Job.getInstance(conf, "MRStep2");
		job.setJarByClass(MRStep2.class);
		job.setMapperClass(Map.class);
		job.setCombinerClass(Reduce.class);
		job.setReducerClass(Reduce.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		System.exit(job.waitForCompletion(true) ? 0 : 1);		
	}
}


