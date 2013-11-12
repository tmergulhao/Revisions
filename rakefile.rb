EXECFLAGS = ""
TOPFLAGS = "-lsqlite3"

task :clean do
  sh "rm objects/* revisions"
end

task :default => ['main.o', :link, :run]

task :stub do
  Rake::Task['command.o'].prerequisites.replace(
      ['entities.o', 'tests.o', 'controller.stub.o'] )
end

task :test => [:stub] do
  EXECFLAGS << "--test"
  Rake::Task[:default].invoke
end

task :link do
  sh "g++ #{TOPFLAGS} objects/*.o -o revisions"
end

task :run do
  sh "./revisions #{EXECFLAGS}"
end

rule '.o' do |t|
  sh "g++ -c -Iincludes sources/#{t.name.chop.chop}.c++ -o objects/#{t.name}"
end

file 'main.o' => ['command.o']

file 'command.o' => ['entities.o', 'tests.o', 'controller.o']
file 'controller.o' => ['persistence.o', 'entities.o']
file 'controller.stub.o' => ['persistence.o', 'entities.o']

file 'tests.o' => ['entities.o']
file 'persistence.o' => ['entities.o']
file 'entities.o' => ['basetypes.o']
file 'basetypes.o'
