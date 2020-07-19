.PHONY: all clean package docker docker_push docker_alpine builddocs localdocs deploydocs test test_valgrind

graph_race: hang
	cd graph_race; \
	make;
.PHONY: graph_race

hang: all
	cd hang; \
	make;
.PHONY: hang

all:
	@$(MAKE) -C ./src all

clean:
	@$(MAKE) -C ./src $@

clean-parser:
	$(MAKE) -C ./deps/libcypher-parser distclean

clean-graphblas:
	$(MAKE) -C ./deps/GraphBLAS clean

package: all
	@$(MAKE) -C ./src package

docker:
	@docker build . -t redislabs/redisgraph

docker_alpine:
	@docker build . -f Dockerfile.alpine -t redislabs/redisgraph:alpine

docker_push: docker
	@docker push redislabs/redisgraph:latest

builddocs:
	@mkdocs build

localdocs: builddocs
	@mkdocs serve

deploydocs: builddocs
	@mkdocs gh-deploy

test:
	@$(MAKE) -C ./src test

memcheck:
	@$(MAKE) -C ./src memcheck

format:
	astyle -Q --options=.astylerc -R --ignore-exclude-errors "./*.c,*.h,*.cpp"
