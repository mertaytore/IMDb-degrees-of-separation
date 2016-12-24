# IMDb-degrees-of-separation
Degrees of separation applied to IMDb film dataset.

This repository implements the idea of [Six degrees of separation](https://en.wikipedia.org/wiki/Six_degrees_of_separation). The idea is implemented with IMDb's [datasets](http://www.imdb.com/interfaces)

- The dataset is processed through a MapReduce algorithm to have a meaningful data. 
- IMDb_adjustment/trim_dataset.sh was ran to get the data needed for MapReduce steps. 
- Next, we processed the dataset in two steps of MapReduce, /HADOOP/try.jar and /HADOOP/try2.jar. 
- Having obtained and output from second MapReduce algorithm, to remove duplicated (if by chance any) IMDb_adjustment/rm_duplicates.py was ran. This step gives us a graph that has every actors' friends that has took a role in the same movie.
- Lastly, resulting graph is inserted into an ANF Algorithm to find the average degrees of separation among all actors.

## Requirements
* [Hadoop](https://github.com/apache/hadoop) for MapReduce
* Python 3.x for duplicate removal
* Gephi - graph visuals

## A graph visualization with ~9000 nodes (actors)
![9k nodes](https://github.com/mertaytore/IMDb-degrees-of-separation/blob/master/9k_nodes.jpg "A visualization with 9k nodes")

### Questions?
Reach out to us!
- :octocat: @mertaytore
- :octocat: @gokhansim
- :octocat: @ebsenol
- :octocat: @orhca
