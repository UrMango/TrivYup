import React from 'react';
import { useCountdown } from '../../hooks/useCountdown/useCountdown';

const CountdownTimer = ({ targetDate }) => {
  const [days, hours, minutes, seconds, total] = useCountdown(targetDate);

  return (<h2>{total < 0 ? 0 : total}</h2>);
};

export default CountdownTimer;