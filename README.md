# ML
Machine learning (implementation of linear regression algorithm from ML class of Andrew Ng)

Linear regression with one variable
You will implement linear regression with one variable to predict profits for a food truck. Suppose you are the CEO of a restaurant franchise and are considering di erent cities for opening a new outlet. 
The chain already has trucks in various cities and you have data for profi ts and populations from the cities.
You would like to use this data to help you select which city to expand to next.
The xy.txt contains the dataset for our linear regression problem. The first column is the population of a city and the second column is the prfitt of a food truck in that city. A negative value for pro t indicates a loss.

####Screenshots

![Alt text] (https://github.com/s-chepurnov/ML/blob/master/images/soft.png)

It's the example of Qt program which contains 4 classes:

-MyWindow (Displays our data)
-MyModel (Model View Controller from Qt Framework)
-Predict (Compute values of profit for some city with certain population by linear regression model)
-Plot (plot the graph with MVC, the biggest difficult is the new coordinate system of training data)

When you start the program you need to choose the text file with training data. Base on these data, program predict some new values.
For example, for city with a population 35,000, we predict a profit of 4519,76$
