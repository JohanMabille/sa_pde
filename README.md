## Development workflow

### Before starting

Fork the repo (click on the fork button near the top right corner), then clone it on your machine
and setup the upstream remote accordingly. For instance, if your github name is JohnDoe:

```bash
git clone https://github.com/JohnDoe/fqs_pde1d.git
cd fqs_pde1d
git remote add upstream https://github.com/JohanMabille/fqs_pde1d.git
```

The URLs can be copied with the `Clone or Download` green button. Then check that everything is ok

```bash
git remote -v
```

You should see 4 lines, two for `origin` with the URL of your fork, and two for `upstream` with the URLs
of the original repo.


The development workflow should respect the following principle:
- never commit on master, always create a branch dedicated to the feature you are developing
- do small changes, commit ofter, open small PRs so your mates can quickly review and merge them
- always rebase on master before pushing for opening a PR
- you should not merge your own PRs

### Use Case 1: you start to develop a new feature

First, be sure you master is up to date; on your remote fork on github (here `JohnDoe/fqs_pde1d`)
you should see `This branch is even with JohanMabille/fqs_pde1d`. If not, you need to update:

```bash
git pull upstream master
git push origin master
```

The first command update your local `master` branch with the changes in `JohanMabille:master`, the second
one push the changes from your local `master` to your remote fork.

Then create a new branch and start to work:

```bash
git checkout -b condition
```

This line creates the `condition` branch (because you want to work on the boundary conditions for instance),
and make it your current branch. Now everything you commit will be recorded in this branch, not in master.

When your implementation is done (check that it compiles, better code a test and have it passing), you're ready
to commit your change. First ensure you are on the right branch:

```bash
git branch
```

This should list all the available branches, the current one should be in a different color and/or prefixed with
a star. Now run `git status` to get a list of the files you've changed. Everything listed in green is ready to be
commited, everything in red must be added first (except if you don't want to commit this change); assume you've
changed `pde_boundary_conditions.hpp` and `pde_boundary_conditions.cpp`, then run:

```bash
git add pde_boundary_conditions.hpp
git add pde_boundary_conditions.cpp
git status
git commit -m "Implementation of boundary conditions"
```

The `git status` is not mandatory, it just helps to check the files were added (they should be listed in green).
Try to write meaningful messages for the commits, they will help you (and your mates) remember what the commit
is about.

Now that you local branch contains your feature, it's time to diffuse it to the world!

```bash
git push origin condition
```

You can then open a Pull Request from the github interface: once it has been pushed, you should see some message
with a yellow background and a button "compare and open PR", or just select your branch and then click on 
"New pull request".

Wait for your team mate to merge your PR. Once it's done, it's time to update your `master` branch and delete
the `condition` branch (you don't need it anymore).

```bash
git checkout master
git pull upstream master
git push origin master
```

The first command change the current branch to be master (you can check that with `git branch` before pulling),
the two following update your local and remote `master` as explained at the beginning of the section. Now your
feature is in `master`, let's delete the `condition` branch:

```bash
git branch -d condition
git push origin :condition
```

The first line delete your local `condition` branch, the second one deletes the remote one.

You can now create a new branch and start to develop a new feature or fix a bug.

### Use case 2: you want to update master while developping

Sometimes you will need to get some features developed by your team mates that were developed in parallel and
that you need to finish your current development. Or some PRs have been merged in master, and you want to ensure
you don't have any conflict before pushing your branch. Assume you are on a branch named `grid` and you want
to update master. First, save your current development:

```bash
git add grid.hpp
git add grid.cpp
git commit -m "implementation of a grid"
```

Then update master:

```bash
git checkout master
git pull upstream master
git push origin master
```

You can now rebase your `grid` branch, that is, putting it after the changes you pulled in `master`:

```bash
git checkout grid
git rebase master
```

It is highly recommended to always rebase on `master` before pushing for a PR.

### Cheatsheet

**Commit**

- `git status`: list all the changes not commited yet.
- `git add filename`: record the file `filemane` so it will be included in the next commit
- `git commit -m "commit message"`: commit all the files recorded with `git add` to the current branch
- `git log -n 10`: list the 10 last commits on the current branch

**branches**

- `git branch`: list the available local branches; the current one is in a different color or prefixed with a star.
- `git checkout my_branch`: set the current branch to `my_branch`. This one must already exist.
- `git checkout -b my_branch`: creates a new branch calle `my_branch` and set the current branch to it.
- `git rebase branch_name`: rebase the current branch to the branch `branch_name`.

**remote**

- `git pull remote_name branch_name`: update the current branch with the changes from the branch `branch_name`
of the remote repo `remote_name`.
- `git push remote_name branch_name`: push the branch `branch_name` to the remote repo `remote_name`.
- `git push remote_name :branch_name`: delete the branch `branch_name` from the remote repo `remote_name`.
- `git remote -v`: list the available remote repos and their URLs.

