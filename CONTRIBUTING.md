# Contributing

This guide will provide you with clear instructions on how you can contribute to our project. It will mark important standards and expectations, this will help maintain project quality and allow for an effective collaboration.

With this guide we want to provide you with an easy way to get started and encourage you to participate.

## Issue reports

You can report issues inside the Github issue tab.

Firstly, check the latest version to see if the issue persists, if it persists, try to create a Minimal Reproduction Project which is a small Godot project using our library that reproduces the issue, include the steps if any.

If you run into a bug which wasn't present in an earlier version (regression), please mention it and clarify which versions you tested (both the one(s) working and the one(s) exhibiting the bug).

## Proposals and improvements

The issue tab is not designed for proposals or improvements, please use the discussion tab with the correct category instead.

## Making pull requests

To make pull requests make sure that it's desired. When making improvements make sure you created a discussion or talked with others about it. If you aren't sure about the specific implemenation, it's best to discuss it with others.

Fork the repository, create a new branch describing your feature, make changes and commit, push your branch and create a PR.

Make PRs that have one specific purpose. Avoid Large PRs that can overwhelm reviewers. Break down substantial changes into smaller, manageable chunks.

Use a descriptive title that summarizes the purpose of the PR. The description should include what changes were made and why, add any relevant context or links to issues.

Write meaningful commit messages which are clear and concise explanations of changes made.

When updating your fork with upstream changes, please use git pull --rebase to avoid creating "merge commits". Those commits unnecessarily pollute the git history when coming from PRs.

Keep the Branch Up-to-Date, Regularly sync your branch with the base branch (ex  main) to avoid merge conflicts and ensure that your changes are compatible with the latest code.

## Branches

main (The current stable release)
├─ develop (The current version development)
│   ├─ release/ (Branches that stabilize for a new version before merging to main)
│   ├─ feature/ (New features for the upcoming version)
│   └─ bugfix/ (Bug fixes and adjustments for the upcoming version)
├─ v1.0 (Maintains the 1.0 version)
│   ├─ feature/(name) (new features or enhancements)
│   └─ bugfix/ (Bug fixes for the 1.0 version)
├─ v2.0 (Maintains the 2.0 version)
│   ├─ feature/(name)
│   └─ bugfix/
└─ hotfix/ (Immediate patches for the stable release)

Now we don't want to complicate stuff as this is just a library not an application.
That means only few versions will be maintained and they might not have all the new features or enhancements, the updates within a maintained version will be easy to upgrade.

Update to a higher major version is likely to require additional steps or rework to be done.
We use semantic versioning: MAJOR.MINOR.PATCH.

### General stuff

1. Don’t wait for a PR to be fully complete to request a review. Early feedback can help identify issues sooner, saving time in the long run.
2. If your changes require updates to documentation (ex. README files, wikis), include those updates in your PR.
3. Follow the project coding standards, Consistency in code style makes it easier for others to read and maintain the code.
4. Actively engage with reviewers by addressing comments and suggestions. Be open to making changes based on feedback.
5. Utilize labels and milestones to categorize your PR for easier tracking and organization. This helps in identifying the state of the PR within the broader context of the project.

## Standards

We use [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

## What we use

1. Scons - To manage build process
2. C++ compiler

## Finally

Check the [Code of Conduct](./CODE_OF_CONDUCT.md)

And most importantly don't be afraid of contributing, we all make mistakes we can learn from. Our community is open to all programmers from beginners to pros! :D
