Module.toggleInput = (toggle) => {
  const setEventEnable = cwrap('setEventEnable', null, ['boolean']);
  setEventEnable(toggle);
};
