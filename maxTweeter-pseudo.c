MAXLENGTH = 99 #maximum line length, not actual value yet

int  main(inputfile){
	File file = openfile(inputfile); #need to check if this is successful
	char[MAXLENGTH] line = file.getline();
	char[MAXLENGTH][MAXLENGTH] tokens = strtok(line);
	int nameIndex = findNameindex(tokens);
	while(line in file){
		line = file.getline();
		tokens = strtok(line);
		name = getname(tokens); #Add counting code here
	}
}

int findNameindex (char** tokens){
	int i = 0;
	for(token in tokens){
		if(token == "name") return i;
		i++;
	}
	bail();
	return null;
}

void bail(){
	printf("Invalid Input Format");
}