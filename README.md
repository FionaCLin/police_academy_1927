

<body class="container" data-gr-c-s-loaded="true">
<header id="jumbotron page-header">
<h1 class="title"><center><strong>
<a href="https://fionaclin.github.io/index.html">Home</a>
</strong></center>
</h1>
</header>
<header class="jumbotron text-center">

<h1 id="police-academy-1927">police academy 1927</h1>
<p class="lead">
<small><strong>Sunday 5th February 2017 </strong></small>
</p>
</header>
<p class="text-center lead">
— <a href="#setting-up">setup</a> — <a href="#program-inputs">inputs</a> — <a href="#the-tasks">tasks</a> —
</p>

<p>In this assignment, you are the police! You will control 4 detectives as they travel through a network of cities trying to catch a thief.</p>
<p>The police are aiming for any of the four detectives to catch the thief before they escapes to the getaway city, and before the time runs out… and the aim of the thief is to reach the getaway before time runs out, and before being caught.</p>
<p>In our simulation, the detectives have a map of the city, but do not know where the thief is or where he is trying to get to. The thief also has a map but does not really know how to use it and wanders randomly through the cities trying to reach the goal destination. The detectives employ different strategies depending on what they have been assigned to.</p>
<h2 id="setting-up">Setting Up</h2>
<p>The supplied files are in <samp><a href="https://github.com/FionaCLin/assign2Comp1927/tree/setup-README/files">https://github.com/FionaCLin/assign2Comp1927/files</a></samp>. Change to your assignment 2 directory, and copy them down by running</p>
<pre><code>$ cp ./files/* .</code></pre>
<p>If you’ve done the above correctly, you should find the following files now in the directory:</p>
<dl>
<dt><code>Makefile</code></dt>
<dd><p>This controls compilation of the program. You only need to modify this if you create additional files for your implementation. It <strong>must</strong> produce an executable called <code>assn2</code>.</p>
</dd>
<dt><code>Graph.h</code></dt>
<dd><p>Graph ADT interface. Provides an interface for basic graph functionality. May be extended to incorporate more functionality. We assume all graphs in this assignment are undirected, weighted graphs and are connected. <strong>Do not change the function prototypes we supply.</strong></p>
</dd>
<dt><code>Graph.c</code></dt>
<dd><p>This is just a stub file that you need to implement yourself. You can use any of the lab code or adapt any of the code from lectures to do this.</p>
</dd>
<dt><code>Agent.h</code></dt>
<dd><p>Agent ADT interface. This is an interface that represents an ‘agent’ in the game. An ‘agent’ represents a detective or a thief. This interface includes functions to allow the agents to interact with the client program.</p>
</dd>
<dt><code>Agent.c</code></dt>
<dd><p>Agent ADT implementation. This partially implements the Agent ADT and supplies the implementation for the <code>RANDOM</code> movement strategy. This will need to be completed by you. Make sure you understand what has already been supplied.</p>
</dd>
<dt><code>main.c</code></dt>
<dd><p>The client program that runs the game. This program reads in the data and creates a graph that represents a map of the city. The 5 agents are also created and a game starts. This will need to be completed by you.</p>
</dd>
<dt><code>input/cities*.data</code> files</dt>
<dd><p>Sample test files to use as a starting point for your testing. Some test files have graphs with small numbers of cities, some with more; some have informants, some don’t, etc… but you should also create your own test files.</p>
</dd>
<dt><code>input/agentsS*.data</code> files</dt>
<dd><p>Sample test files that you can use once you have completed the different stages of the assignment. agents1.data should work if you have implemented stage 1 and above, agents2.data should work if you have implemented stage 2 and above, and so on. Note that stage 4 must be tested by using one of the cities data files with informants. And, of course, you should create your own <code>agents.data</code> files for testing.</p>
</dd>
</dl>
<p>For this assignment, all files are given to you as a starting point. You may modify them in anyway you like. However you must, of course, make sure your finished implementation follows the behaviour of the model output.</p>
<h2 id="program-inputs">Program Inputs</h2>
<h3 id="command-line-arguments">Command-Line Arguments</h3>
<pre><code>usage: assn2 &lt;city-data&gt; &lt;agent-data&gt; &lt;cycles&gt; [&lt;seed&gt;]</code></pre>
<p>The program requires 3 command line options with an optional fourth. The command line arguments are</p>
<ol style="list-style-type: decimal">
<li><p>the name of the City data file,</p></li>
<li><p>the name of the Agent data file,</p></li>
<li><p>the maximum number of cycles in the game, and</p></li>
<li><p><em>(optionally)</em> a random seed value; by using the same seed, you can produce the same ordering of ‘random’ moves and repeat exactly the same situation.</p></li>
</ol>
<h3 id="city-data">City Data</h3>
<p>The first line shows how many cities are in the graph. Then, for every city there will be a line of data listing its edges, with weights. This is an undirected graph, so if there is an edge from 0 to 5 with weight 29 there should be an edge from 5 to 0 with a weight 29. After the edges are listed each vertex will have data segment with a value of either ‘n’ or ‘i’ and then its actual string representation. The ‘n’ indicates that it is a normal city. The ‘i’ indicates the city has an informant there.</p>
<pre><code>10
0 5 29 1 41 6 60 7 50 8 40 n sydney
1 2 51 5 29 n adelaide
2 n melbourne
3 5 30 4 36 n perth
4 3 36 9 20 n darwin
5 1 29 0 29 3 30 6 10 n hobart
6 n auckland
7 n madrid
8 n new york
9 n brisbane</code></pre>
<h3 id="agent-data">Agent Data</h3>
<p>The first line of data represents information about the thief. The first number represents the amount of stamina the thief starts with. The second number indicates where the starting location of the thief is. The third number represents the goal city of the thief. This is followed by a string representation of the thief.</p>
<p>The next four lines represent the 4 detectives. Each detective is also given a starting stamina and a starting location. However the third integer represents the strategy that the detective is assigned. This is followed by a string representation of the detective.</p>
<pre><code>10 5 6 T
1 2 0 D1
1 3 1 D2
5 1 2 D3
5 4 2 D4</code></pre>
<h2 id="the-tasks">The Tasks</h2>
<h3 id="task-0-graph-black-box-unit-testing-4-marks">Task 0: Graph Black-Box Unit Testing <small>4 marks</small></h3>
<p>You must write a <code>testGraph.c</code> that tests the functions defined in the given <code>Graph.h</code> file. You must create <code>assert(3)</code>-based tests. We run your <code>testGraph.c</code> code with our own working and broken graph implementations to check they pass and fail the implementations accordingly.</p>
<p>Only use and test functions from the original <code>Graph.h</code>. Do not need to submit tests for any additional functions you add to your graph when you complete the other tasks of the assignment.</p>
<p>You do not need <code>assert(3)</code>-based tests for the functions <em>show</em> or <em>destroyGraph</em>.</p>
<h3 id="task-1-assignment-diary-1-mark">Task 1: Assignment Diary <small>1 mark</small></h3>
<p>As you complete your work on this assignment, you must maintain an assignment diary where you will reflect on what you have done. In a text file called <code>assn2Diary.txt</code>, place the date and time of your work together with some brief comments of the work you have completed such as what you worked on, what you accomplished and what bugs you fixed.</p>
<p>You should discuss your choices of data structures and additional ADTs you have used in your implementation. It should also discuss how you have tested your implementation.</p>
<p>You may like to base your assignment diary on logs from a version control system, like Git or Subversion. Make sure your commit messages are informative!</p>
<h3 id="task-2-implementation">Task 2: Implementation</h3>
<p>You may create additional <code>.h</code> and <code>.c</code> files to use in your implementation for all/any of the stages.</p>
<h4 id="stage-0-random-strategy-1.5-automarks">Stage 0: <code>RANDOM</code> strategy <small>1.5 automarks</small></h4>
<p>For stage 0 we will test detectives using the random strategy only. The random strategy has been implemented, however you will need to modify the provided code in these ways to pass stage 0.</p>
<p>The data for each vertex including whether there is an informant in the city and the name of the city is read in by the program, but is never stored in the graph or displayed when printing out the stats. You must implement this.</p>
<p>You must complete the implementation of a weighted graph in <code>Graph.c</code> You should decide which implementation will make it easiest to implement the rest of the assignment!</p>
<p>Make sure all the information shown in stats and map have all the correct details.</p>
<p>Stamina limitations must also be implemented. To do this, each time an agent makes a move, the weight of the edge followed is deducted from the stamina. Edges that the agent does not have enough stamina for, are not considered legal moves. This means there may be no legal moves for the agent to randomly select. If the detective does not have any legal moves left, due to not having enough stamina, he must remain in the same city for another cycle. Remaining in the same city for a cycle resets the agents stamina back to the original level.</p>
<p>You must also implement winning or losing the game. The supplied implementation finishes the game, only when time runs out. You need to implement the other winning conditions.:</p>
<ul>
<li><p>The detectives win the game if at the end of the turn, they are located in the same city as the thief.</p></li>
<li><p>The thief wins the game if at the end of a turn they is located in the goal city and there are no detectives there.</p></li>
<li><p>If the thief reaches the goal location at the same time as one of the detectives, the detective catches the thief and wins.</p></li>
</ul>
<p>Note: If one of the detectives starts in the same city as the thief, the thief is caught immediately. However, throughout the game, the thief is caught only if one of the detectives is in the same city as the thief <em>at the end of the cycle</em>.</p>
<h4 id="stage-1-cheapest_least_visited-strategy-2.4-automarks">Stage 1: <code>CHEAPEST_LEAST_VISITED</code> strategy <small>2.4 automarks</small></h4>
<p>If a detective is assigned this strategy, it means that at every opportunity he has to move, he will move to the city he has visited the least number of times, out of the legal options that are available. This means the detective must work out what cities are actually adjacent to the current city and pick from those the one that has been visited the least. In situations where there are more than one location with the same number of visits, the one with the smallest weight is chosen. If there is more than one location with the same number of visits <em>and</em> the same weight, the one with the lowest Vertex Id should be chosen.</p>
<p>The stamina limitations described in stage 0 should also be enforced for this stage and all stages of the assignment, so cities that the agent does not have enough stamina to visit are not considered legal moves.</p>
<p>This stage will be tested by supplying agent files with only this or the random strategy being used.</p>
<h4 id="stage-2-dfs-strategy-2.2-automarks">Stage 2: <code>DFS</code> strategy <small>2.2 automarks</small></h4>
<p>In this stage a DFS strategy must be implemented. When following this strategy, the agent maps out an entire route that will take him through every city on the map using the DFS algorithm. At every cycle, the agent attempts to move to the next city on the plan. If the agent does not have enough stamina he will wait in the same ciy to recover. When the agent has visited all cities at least once, a new dfs path from the final location is mapped out and is followed.</p>
<h4 id="stage-3-least-turns-path-1.4-automarks">Stage 3: Least Turns Path <small>1.4 automarks</small></h4>
<p>In this stage we will test your implementation using city data with informants. Thus at any cycle during the game a detective might go to a city where there is an informant. In this situation the detective finds out where the thief is currently located. The detective must then find the path to that location that will take the least number of turns. Of course the thief may be gone by the time the detective gets there and the detective must restart his original strategy from his new location. Any cities the detective passes through on the shortest path are counted as being visited if the detective returns to the <code>CHEAPEST_LEAST_VISITED</code> strategy. The detective may also pass through a city with another informant in which the detective would find a new least turns path from the current location.</p>
<p>You must take into account the stamina of the agent. For example, if one path requires the agent to travel through 3 vertices, but would have to rest twice (5 turns), that is more turns that an agent travelling through 4 vertices but not having to rest (4 turns).</p>
<p>If there are 2 paths that would take equal turns, choose the one that results in the agent having the most stamina when he reaches his goal.</p>
<p>If there are 2 paths that would take equal turns and would result in the agent having the same resulting stamina, either path is valid. (We will not autotest this situation).</p>
<h3 id="the-model-solution">The Model Solution</h3>
<p>A sample solution is available at <code>./assn2</code>. The program takes 3 command line arguments as outlined above. These are the filename with the city data, the filename with the agent data, the maximum number of cycles and it optionally takes a fourth command line argument that is used to seed the random number generator that is used for random movement. This is provided to facilitate automarking and testing.</p>

<h4 id="the-commands">The Commands</h4>
<p>Once the program has started the user will be prompted for input. The available commands are listed below:</p>
<dl>
<dt><kbd>run</kbd></dt>
<dd><p>This will run an entire simulation, printing out a trace of the agents location for each cycle of the game. It will print out how the game finished ie with the thief being caught, getting away, time running out.</p>
</dd>
<dt><kbd>step</kbd></dt>
<dd><p>This command will run just one cycle of the game, printing out the new location of the agents for the next cycle. If the game finished in that cycle, it will also print out how the game finished. This allows the user to step through the game one cycle at a time.</p>
</dd>
<dt><kbd>stats</kbd></dt>
<dd><p>This prints out statistics about the agent. This includes the name of the agents’ current location, the name of the agent’s goal location if it is the thief or was given the thief’s location, and the agents’ stamina.</p>
</dd>
<dt><kbd>display</kbd></dt>
<dd><p>This will display the current locations of all agents.</p>
</dd>
<dt><kbd>map</kbd></dt>
<dd><p>This prints out the graph connectivity information that represents the map of the city.</p>
</dd>
<dt><kbd>quit</kbd></dt>
<dd><p>Quits the game!</p>
</dd>
</dl>
<h4 id="sample-outpt-stage-0">Sample Outpt (Stage 0)</h4>
<p>In this example all detectives are following the <code>RANDOM</code> strategy (strategy 0). The thief uses the random strategy.</p>
<div class="panel panel-default">
<div class="panel-heading">
<tt>$ <b>./assn2 input/citiesSmall.data input/agentsS0.data 10 6</b></tt>
</div>
<pre><code>POLICE ACADEMY 1927

Red alert! A thief is on the run.
Agents, to your cars. You have 10 hours.

Hour 0
  T  D1  D2  D3  D4
  3   1   1   1   1

Enter command: map
V=4, E=3
0-1 : 41 0-2 : 900
1-0 : 41
2-0 : 900 2-3 : 30
3-2 : 30

Enter command: stats
Hour 0
T 1000 california (3) melbourne (0)
D1 100000 perth (1)
D2 5000 perth (1)
D3 50 perth (1)
D4 500 perth (1)

Enter command: step
Hour 1
  T  D1  D2  D3  D4
  2   0   0   0   0

Enter command: stats
Hour 1
T 970 darwin (2) melbourne (0)
D1 99959 melbourne (0)
D2 4959 melbourne (0)
D3 9 melbourne (0)
D4 459 melbourne (0)

Enter command: step
Hour 2
  T  D1  D2  D3  D4
  3   1   2   0   1

Enter command: stats
Hour 2
T 940 california (3) melbourne (0)
D1 99918 perth (1)
D2 4059 darwin (2)
D3 50 melbourne (0)
D4 418 perth (1)

Enter command: display
Hour 2
  T  D1  D2  D3  D4
  3   1   2   0   1

Enter command: run
Hour 3
  T  D1  D2  D3  D4
  2   0   3   1   0

Hour 4
  T  D1  D2  D3  D4
  0   1   2   1   1

T got away to melbourne (0)
GAME OVER: YOU LOSE - THIEF GOT TO GETAWAY</code></pre>
</div>
<h4 id="sample-output-stage-1">Sample Output (Stage 1)</h4>
<p>In this example all detectives are using the <code>CHEAPEST_LEAST_VISITED</code> strategy and the thief is following the usual random strategy.</p>
<div class="panel panel-default">
<div class="panel-heading">
<tt>$ <b>./assn2 input/citiesMedium.data input/agentsS1.data 10 4</b></tt>
</div>
<pre><code>POLICE ACADEMY 1927

Red alert! A thief is on the run.
Agents, to your cars. You have 10 hours.

Hour 0
  T  D1  D2  D3  D4
  9   8   7   6   2

Enter command: run
Hour 1
  T  D1  D2  D3  D4
  4   0   0   5   1

Hour 2
  T  D1  D2  D3  D4
  9   5   5   0   5

Hour 3
  T  D1  D2  D3  D4
  4   6   6   8   6

Hour 4
  T  D1  D2  D3  D4
  3   5   5   0   0

Hour 5
  T  D1  D2  D3  D4
  5   6   1   1   8

Hour 6
  T  D1  D2  D3  D4
  1   6   2   2   0

Hour 7
  T  D1  D2  D3  D4
  0   0   1   1   7

D1 caught the thief in sydney (0)
YOU WIN - THIEF CAUGHT!</code></pre>
</div>
<h4 id="sample-output-stage-2">Sample Output (Stage 2)</h4>
<p>In this example detectives 3 and 4 use the DFS strategy. In this strategy they do a depth first traversal from their starting points and follow this at each cycle. If they do not have the stamina to go to the next city on their route, they remain at the same location to regai2Bn their stamina and continue on the set path. (This happens even if there were other options they did have the stamina for.)</p>
<p>In this example detective 1 and 2 are sill following the <code>CHEAPEST_LEAST_VISITED</code> strategy and the thief is of course using the <code>RANDOM</code> strategy.</p>
<div class="panel panel-default">
<div class="panel-heading">
<tt>$ <b>./assn2 input/citiesMedium.data input/agentsS2.data 10 2</b></tt>
</div>
<pre><code>POLICE ACADEMY 1927

Red alert! A thief is on the run.
Agents, to your cars. You have 10 hours.

Hour 0
  T  D1  D2  D3  D4
  9   2   8   1   2

Enter command: run
Hour 1
  T  D1  D2  D3  D4
  4   1   0   0   1

Hour 2
  T  D1  D2  D3  D4
  9   5   5   5   0

Hour 3
  T  D1  D2  D3  D4
  4   6   6   3   0

Hour 4
  T  D1  D2  D3  D4
  9   5   5   4   5

Hour 5
  T  D1  D2  D3  D4
  4   5   1   9   3

Hour 6
  T  D1  D2  D3  D4
  4   0   2   4   4

D3 caught the thief in darwin (4)
YOU WIN - THIEF CAUGHT!</code></pre>
</div>
<h4 id="sample-output-stage-3">Sample Output (Stage 3)</h4>
<p>In this example, detective D1 and D2 start with <code>CHEAPEST_LEAST_VISITED</code> strategy and detective 3 and 4 start with the DFS strategy. However detective 1 and 4 starts off in a city with an informant (this is indicated by the <code>*</code> character on the display), so straight away switch to the strategy of going along the shortest path to the thiefs current location (city 9). Detective 4 reaches the destination by hour 5 but the thief is no longer there. However the other detectives have found the thief by this stage anyway. Detective 1 is following the shortest path from 8 to 9, but has to stop at Hour 4 to regain stamina. Detective 2 finds an informant in city 1 in hour 1 and goes via the shortest path from vertex 1 to 4. In hour 3 detective 3 finds an informant and goes via the shortest path to vertex 4.</p>
<p>So D1 calculated that the path that takes the least number of turns to get from 8 to 9 (taking into account his/her stamina) is 8,0,5,3 (rest) ,4,9 (cost 6 turns).</p>
<p>D1 calculates the path to be 8,0,5,3,4,9 so it costs 5 turns.</p>
<p>In Hour 1, D2 runs into an informant and calculates the path from 1 to 4. (1,5 (rest),3,4)</p>
<p>In Hour 3 D3 runs into an informant and calculates the path from 1 to 4.</p>
<div class="panel panel-default">
<div class="panel-heading">
<tt>$ <b>./assn2 input/citiesInformants.data input/agentsS3.data 20 2</b></tt>
</div>
<pre><code>POLICE ACADEMY 1927

Red alert! A thief is on the run.
Agents, to your cars. You have 10 hours.

Hour 0
  T  D1  D2  D3  D4
  9   8*  2   6   8*

Enter command: run
Hour 1
  T  D1  D2  D3  D4
  4   0   1*  0   0

Hour 2
  T  D1  D2  D3  D4
  9   5   5   0   5

Hour 3
  T  D1  D2  D3  D4
  4   3   5   1*  3

Hour 4
  T  D1  D2  D3  D4
  9   3   3   5   4

Hour 5
  T  D1  D2  D3  D4
  4   4   4   3   9

D1 caught the thief in darwin (4)
YOU WIN - THIEF CAUGHT!</code></pre>
</div>
<hr>
