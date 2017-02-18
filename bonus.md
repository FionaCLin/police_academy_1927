</head>
<body class="container" data-gr-c-s-loaded="true">
<header class="page-header">
<h1 class="title">COMP1927 17x1 / Assignment 2</h1>
</header>

<header class="jumbotron text-center">

<h1 id="master-thief">master thief</h1>
<p class="lead">
<strong>Marks:</strong> 2 <em>bonus</em> marks<br><strong>Submit:</strong> <code>1927 classrun 17x1 give assn2Bonus</code><br><strong>Due:</strong> 23:59 Friday 3rd February 2017<br><small><strong>no late submissions</strong></small>
</p>
</header>
<p class="text-center lead">
— <a href="https://www.cse.unsw.edu.au/~cs1927/17x1/assignments/assn2/bonus.html#the-tasks">tasks</a> — <a href="https://www.cse.unsw.edu.au/~cs1927/17x1/assignments/assn2/bonus.html#assessment">assessment</a> — <a href="https://www.cse.unsw.edu.au/~cs1927/17x1/assignments/assn2/bonus.html#marks">marks</a> —
</p>

<h2 id="the-tasks">The Tasks</h2>
<h3 id="task-0-makefile-0-marks">Task 0: Makefile <small>0 marks</small></h3>
<p>Write (or modify!) a Makefile for the bonus component, which should be capable of producing <code>assn2Bonus</code>. We will be using your Makefile to compile your assignment for automarking; if you do not provide one, or yours cannot produce <code>assn2Bonus</code>, you will receive 0 for the automarking.</p>
<h3 id="task-1-thief-strategy-implementation-2-marks">Task 1: Thief Strategy Implementation <small>2 marks</small></h3>
<p>You must modify the assn2 program and implement a strategy for the thief.</p>
<p>Assume the thief has a map of the cities and knows where the getaway location is. Also assume that the thief knows the location of each detective, but does not know the strategy or stamina of the agent. Also assume that for this part of the assignment no detectives will be using random strategy. The thief does not know where the informants for the detectives are.</p>
<p>The aim is to implement a clever strategy for the thief that increases the liklihood of getting away, or at least holding off being caught for as long as possible.</p>
<h3 id="task-2-diary-0-marks">Task 2: Diary <small>0 marks</small></h3>
<p>You must maintain an <code>assn2BonusDiary.txt</code>, as with the normal version of the assignment. You will need to provide an entry in it to explain your strategy and the basics of how it works. You will lose 1 mark if it is missing or empty.</p>
<h2 id="assessment">Assessment</h2>
<p>This will be run as a competition.</p>
<p>All entries, along with the original random thief from the <code>assn2Model</code> will be run in different situations.</p>
<p>Different situations will include different maps, different starting locations, different seeds, different detective strategies etc.</p>
<p>Any submissions that do not follow the rules of the game will be disqualified. If they seem like a serious attempt that unintentionally broke the rules, they will get 0.5 marks, but will not be run during the competition.</p>
<p>During the competition, the number of times the thief gets away will be recorded. The number of times the thief is caught will also be recorded, along with as the number of hours the thief can resist being caught by the detectives in situations when the thief gets caught or time runs out..</p>
<p>The score is calculated by the number of getaways minus the number of times the thief is caught.</p>
<p>The person with the highest score wins. In cases of ties, the total number of hours the thief resisted being caught will be taken into account.</p>

</div>
<hr>

