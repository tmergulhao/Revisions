TOPFLAGS = "-lsqlite3 "
DFLAGS = ""
EXECFLAGS = ""
TESTINGUNITS = "basetypes.c++"

task :default => ['main.o',:link_run, :clean]

task :stub_before do
  sh "g++ -c #{DFLAGS} persistence.stub.c++"
  sh "mv persistence.stub.o persistence.o"
end
task :stub => [:stub_before, :default, :clean]

task :vanilla_before do
  EXECFLAGS << "--vanilla"
end
task :vanilla => [:vanilla_before,:default, :clean]

task :cover_before do
	DFLAGS << "-fprofile-arcs " << "-ftest-coverage "
	EXECFLAGS = "--test"
end
task :cover => [:cover_before, 'main.o', :link_run, :clean] do
  sh "gcov #{TESTINGUNITS}"
end

task :link_run do
  sh "g++ *.o #{TOPFLAGS}#{DFLAGS}-o compiled.out"
  sh "./compiled.out #{EXECFLAGS}"
end

task :clean do
  sh "rm *.o *.out"
  if DFLAGS != ""
    sh "rm *.gcov *.gcda *.gcno"
  end
end

rule '.o'  => '.c++' do |t|
	sh "g++ -c #{DFLAGS} #{t.source}"
end

file 'main.o' => ['main.c++', 'command.o']
file 'command.o' => ['command.c++', 'command.h', 'basetypes.o', 'tests.o', 'persistence.o']
file 'persistence.o' => ['persistence.c++','persistence.h', 'basetypes.o']
file 'test.o' => ['tests.c++','tests.h', 'basetypes.o']
file 'basetypes.o' => ['basetypes.c++', 'basetypes.h']
