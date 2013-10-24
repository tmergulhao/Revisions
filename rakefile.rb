TOPFLAGS = "-lsqlite3 "
DFLAGS = ""
EXECFLAGS = ""

task :default => ['main.o',:link, :run]

task :vanilla_before do
  EXECFLAGS << "--vanilla"
end
task :vanilla => [:vanilla_before,:default]

task :test_before do
	DFLAGS << "-fprofile-arcs " << "-ftest-coverage "
  EXECFLAGS << "--test"
end
task :test => [:test_before,'main.o', :link, :run, :cover, :clean]

task :link do
	sh "g++ *.o #{TOPFLAGS}#{DFLAGS}-o compiled.out"
end
task :run do
	sh "./compiled.out #{EXECFLAGS}"
end
task :cover do
#	sh "gcov *.o"
end
task :clean do
	sh "rm *.o *.out *.gcov *.gcda *.gcno"
end

rule '.o'  => '.c++' do |t|
	sh "g++ -c #{DFLAGS} #{t.source}"
end

file 'main.o' => ['main.c++', 'command.o']
file 'command.o' => ['tests.o', 'command.c++', 'command.h', 'basetypes.o']
file 'test.o' => ['tests.c++','tests.h', 'basetypes.o']
file 'basetypes.o' => ['basetypes.c++', 'basetypes.h']
