package trial;

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
public class trial{

	public static class Map
	extends Mapper <LongWritable, Text, Text, Text>{

		private Text actor = new Text();
		private Text movie = new Text();

		public void map(LongWritable key, Text value, Context context
				) throws IOException, InterruptedException {
			String str1 ="";
			StringTokenizer itr = new StringTokenizer(value.toString(), ",");
			if (itr.hasMoreTokens())
				str1 = itr.nextToken().trim();
			
			actor.set(str1);
			

			while (itr.hasMoreTokens()) {
				movie.set(itr.nextToken().trim());
				context.write(movie, actor);
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
				if (val.toString() == "\t" || val.toString() == "\n" || val.toString() == "\r") {
				;}
				
				else 
				str = str + val.toString() + ";";
				
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
		Job job = Job.getInstance(conf, "word count");
		job.setJarByClass(trial.class);
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


